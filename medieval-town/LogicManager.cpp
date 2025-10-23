#include "LogicManager.h"
#include "Location.h"
#include "Town.h"
#include "BuildingType.h"
#include "Building.h"
#include "House.h"
#include "Family.h"
#include "Tile.h"
#include "Construction.h"
#include "ConstructionBuilding.h"
#include "ConstructionHouse.h"
#include <iostream> // Pour le log()

using std::string;
using std::make_unique;
using std::make_shared;
using std::multimap;

LogicManager LogicManager::instance; // Instanciation du LogicManager statique

LogicManager::LogicManager() {}

LogicManager& LogicManager::getInstance()
{
	return LogicManager::instance;
}

void LogicManager::setAPI(LogicAPI* newApi)
{
	this->api = newApi;
}

void LogicManager::startGame()
{
	// Création de la ville
	this->town = make_unique<Models::Town>("Lorrez-le-Bocage", 100, 100);
	town->startTown();

	// Création des familles
	this->addFamily("Salviati");
	this->addFamily("Legrand");

	// Initialisation des BuildingTypes
	this->initBuildingTypes();
}

void LogicManager::logicTick()
{
	this->log("--- Jour " + std::to_string(this->town->getDate()) + " ---");

	this->town->logicTick();

	// Log de l'état des familles
	for (const auto family : this->getTown()->getFamilies()) {
		this->log("Famille " + family->getName() + " : or " + std::to_string(family->getGold()) + " - prestige : " + std::to_string(family->getPrestige()));
	}
}

void LogicManager::log(string message) const {
	if(api != nullptr) {
		// Si on est dans le moteur de jeu, on passe par l'API
		api->log(message);
		return;
	}
	std::cout << message << "\n";
}

Models::Town* LogicManager::getTown()
{
	return this->town.get();
}

int LogicManager::addFamily(const string& name)
{
	unique_ptr<Models::Family> family = make_unique<Models::Family>(name);
	int familyId = this->town->addFamily(std::move(family));
	return familyId;
}

void LogicManager::initBuildingTypes()
{
	std::map<Models::Pop, int> goldCostPerPopulation;
	std::map<Models::Pop, int> goldGainPerPopulation;
	std::map<Models::Pop, int> prestigeGainPerPopulation;

	// Initialisation du BuildingType Chapelle
	goldCostPerPopulation = {
		{ Models::Pop::Gueux, 0 },
		{ Models::Pop::Bourgeois, 0 },
		{ Models::Pop::Noble, 0 }
	};
	goldGainPerPopulation = {
		{ Models::Pop::Gueux, 2 },
		{ Models::Pop::Bourgeois, 3 },
		{ Models::Pop::Noble, 4 }
	};
	prestigeGainPerPopulation = {
		{ Models::Pop::Gueux, 2 },
		{ Models::Pop::Bourgeois, 4 },
		{ Models::Pop::Noble, 6 }
	};
	unique_ptr<Models::BuildingType> buildingType_Chapelle = make_unique<Models::BuildingType>(
		"Chapelle",
		"Chapelle",
		5, 5,
		200, 20,
		goldCostPerPopulation,
		goldGainPerPopulation,
		prestigeGainPerPopulation,
		10, 50, 5,
		Models::Service::Priere
	);
	addBuildingType(std::move(buildingType_Chapelle));

	// Initialisation du BuildingType Puits
	goldCostPerPopulation = {
		{ Models::Pop::Gueux, 0 },
		{ Models::Pop::Bourgeois, 0 },
		{ Models::Pop::Noble, 0 }
	};
	goldGainPerPopulation = {
		{ Models::Pop::Gueux, 1 },
		{ Models::Pop::Bourgeois, 1 },
		{ Models::Pop::Noble, 1 }
	};
	prestigeGainPerPopulation = {
		{ Models::Pop::Gueux, 3 },
		{ Models::Pop::Bourgeois, 3 },
		{ Models::Pop::Noble, 3 }
	};
	unique_ptr<Models::BuildingType> buildingType_Puits = make_unique<Models::BuildingType>(
		"Puits",
		"Puits",
		2, 2,
		50, 5,
		goldCostPerPopulation,
		goldGainPerPopulation,
		prestigeGainPerPopulation,
		8, 40, 3,
		Models::Service::Eau
	);
	addBuildingType(std::move(buildingType_Puits));
}

Models::BuildingType* LogicManager::getBuildingType(const string& id)
{
	auto it = buildingTypes.find(id);
	if (it != buildingTypes.end()) {
		return it->second.get();
	}
	return nullptr;
}

void LogicManager::addBuildingType(unique_ptr<Models::BuildingType> buildingType)
{
	this->buildingTypes[buildingType->getId()] = std::move(buildingType);
}

void LogicManager::startConstructionBuilding(const Models::BuildingType& type, Models::Family* family, int x, int y, int rotation)
{
	// Test de la validité de l'emplacement
	if (!this->isValidLocation(x, y, rotation, type.getSizeX(), type.getSizeY())) {
		this->log("Erreur : emplacement invalide pour la construction de " + type.getName() + " a " + std::to_string(x) + " ; " + std::to_string(y));
		return;
	}

	// Création de la Construction
	unique_ptr<Models::ConstructionBuilding> construction = make_unique<Models::ConstructionBuilding>(type, family, x, y, rotation);

	// On log l'événement
	this->log("Debut de la construction de " + construction->getType().getName() +  (family != nullptr ? " par " + family->getName() : "") + " a " + std::to_string(construction->getX()) + " ; " + std::to_string(construction->getY()));

	// On ajoute la Construction dans le cache de localisation
	mapLocations[construction->getX()][construction->getY()] = construction.get();

	if (family != nullptr) {
		// Coût pour la famille
		family->removeGold(type.getGoldConstructionCost());

		// On informe la Family de la nouvelle Construction
		family->addConstruction(construction.get());
	}

	// On informe les tiles aux alentours qu'ils ne peuvent plus recevoir de maison
	this->updateCanHaveHouseAroundConstruction(construction.get());

	// Enfin, on bouge le unique_ptr dans Town qui en a désormais la charge
	town->addConstruction(std::move(construction));
}
void LogicManager::startConstructionBuilding(const string& buildingTypeId, int familyId, int x, int y, int rotation)
{
	Models::BuildingType* type = this->getBuildingType(buildingTypeId);
	if (type == nullptr) {
		this->log("Erreur : BuildingType inconnu pour la construction de bâtiment avec l'ID " + buildingTypeId);
		return;
	}
	Models::Family* family = this->getTown()->getFamily(familyId);
	this->startConstructionBuilding(*type, family, x, y, rotation);
}

void LogicManager::constructionBuildingDone(Models::ConstructionBuilding* construction)
{
	// On crée le nouveau Building qui vient remplacer la Construction
	this->createBuilding(construction->getType(), construction->getFamily(), construction->getX(), construction->getY(), construction->getRotation());
	// Pas besoin de retirer la Construction du cache de localisation car le Building l'écrase

	// On supprime le chantier de construction
	construction->getFamily()->removeConstruction(construction);
	town->removeConstruction(construction);

	// UE : despawn l'objet Construction, petite animation de construction achevée
}

void LogicManager::createBuilding(const Models::BuildingType& type, Models::Family* family, int x, int y, int rotation)
{
	unique_ptr <Models::Building> building = make_unique<Models::Building>(type, family, x, y, rotation);

	// On log l'événement
	this->log("Construction achevee de " + building->getName() + (family != nullptr ? " par " + family->getName() : "") + " a " + std::to_string(building->getX()) + " ; " + std::to_string(building->getY()));

	// On ajoute le Building dans les caches de localisation
	mapLocations[building->getX()][building->getY()] = building.get();
	mapBuildings[building->getX()][building->getY()] = building.get();

	// On ajoute le Building dans la famille (s'il en a une)
	if (family != nullptr)
		family->addBuilding(building.get());

	// On déplace le pointeur unique dans la Town
	town->addBuilding(std::move(building));

	// UE : spawn l'objet Building
}

void LogicManager::destroyBuilding(Models::Building* building)
{
	// On log l'événement
	this->log("Destruction de " + building->getName() + (building->getFamily() != nullptr ? " par " + building->getFamily()->getName() : "") + " a " + std::to_string(building->getX()) + " ; " + std::to_string(building->getY()));

	// On retire le Building des caches de localisation
	mapLocations[building->getX()][building->getY()] = nullptr;
	mapBuildings[building->getX()][building->getY()] = nullptr;

	// On retire le Building de la famille (s'il en a une)
	if (building->getFamily() != nullptr)
		building->getFamily()->removeBuilding(building);

	// On retire ce Building des maisons qu'il servait
	for(auto house : building->getHousesServed()) {
		house->removeService(building->getType().getService());
	}

	// On met à jour le canHaveHouse des tiles autour du Building détruit
	updateCanHaveHouseAroundDestruction(building);

	// On supprime le Building de la Town
	town->removeBuilding(building);
	// UE : despawn l'objet Building, petite animation de destruction
}


void LogicManager::startConstructionHouse(int x, int y, int rotation, int sizeX, int sizeY, int niveau)
{
	// Test de la validité de l'emplacement
	if (!this->isValidLocation(x, y, rotation, sizeX, sizeY)) {
		this->log("Erreur : emplacement invalide pour la construction de House a " + std::to_string(x) + " ; " + std::to_string(y));
		return;
	}

	// Création de la Construction
	unique_ptr<Models::ConstructionHouse> construction = make_unique<Models::ConstructionHouse>(x, y, rotation, sizeX, sizeY, niveau);

	// On log l'événement
	this->log("Debut de la construction d'une maison a " + std::to_string(construction->getX()) + " ; " + std::to_string(construction->getY()));

	// On ajoute la Construction dans le cache de localisation
	mapLocations[construction->getX()][construction->getY()] = construction.get();

	// On informe les tiles aux alentours qu'ils ne peuvent plus recevoir de maison
	this->updateCanHaveHouseAroundConstruction(construction.get());

	// Enfin, on bouge le unique_ptr dans Town qui en a désormais la charge
	town->addConstruction(std::move(construction));
}

void LogicManager::constructionHouseDone(Models::ConstructionHouse* construction)
{
	// On crée la nouvelle House qui vient remplacer la Construction
	this->createHouse(construction->getX(), construction->getY(), construction->getRotation(), construction->getSizeX(), construction->getSizeY(), construction->getNiveau());
	// Pas besoin de retirer la Construction du cache de localisation car
	// On supprime le chantier de construction
	town->removeConstruction(construction);
	// UE : despawn l'objet Construction, petite animation de construction achevée
}

void LogicManager::createHouse(int x, int y, int rotation, int sizeX, int sizeY, int niveau)
{
	unique_ptr<Models::House> house = make_unique<Models::House>(x, y, rotation, sizeX, sizeY, niveau);
	// On log l'événement
	this->log("Maison achevee a " + std::to_string(house->getX()) + " ; " + std::to_string(house->getY()));
	// On ajoute la House dans les caches de localisation
	mapLocations[house->getX()][house->getY()] = house.get();
	mapHouses[house->getX()][house->getY()] = house.get();
	// On déplace le pointeur unique dans la Town
	town->addHouse(std::move(house));
	// UE : spawn l'objet House
}

void LogicManager::destroyHouse(Models::House* house)
{
	// On log l'événement
	this->log("Destruction d'une maison a " + std::to_string(house->getX()) + " ; " + std::to_string(house->getY()));

	// On retire la House des caches de localisation
	mapLocations[house->getX()][house->getY()] = nullptr;
	mapHouses[house->getX()][house->getY()] = nullptr;

	// On retire cette House des bâtiments de service qu'elle utilisait
	for(auto pair : house->getAllServiceBuildings()) {
		pair.second->removeHouseServed(house);
	}

	// On met à jour le canHaveHouse des tiles autour de la maison détruite
	updateCanHaveHouseAroundDestruction(house);

	// On supprime la House de la Town
	town->removeHouse(house);
	// UE : despawn l'objet House, petite animation de destruction
}

Models::Location* LogicManager::getLocationAt(int x, int y)
{
	if (mapLocations.find(x) != mapLocations.end() && mapLocations[x].find(y) != mapLocations[x].end()) {
		return mapLocations[x][y];
	}
	return nullptr;
}

vector<Models::House*> LogicManager::getHousesInRange(int centerX, int centerY, int range) 
{
	// On utilise une multimap pour stocker nos résultats avec la distance au point d'origine comme clé
	multimap<float, Models::House*> ordered_list;

	// On parcourt tous les maisons via le cache de localisation
	int minX = centerX - range;
	int maxX = centerX + range;
	int minY = centerY - range;
	int maxY = centerY + range;

	// On ajuste les bornes pour qu'elles restent dans les limites de la ville
	if (minX < 0) minX = 0;
	if (maxX >= this->town->getSizeX()) maxX = this->town->getSizeX() - 1;
	if (minY < 0) minY = 0;
	if (maxY >= this->town->getSizeY()) maxY = this->town->getSizeY() - 1;

	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			Models::House* house = mapHouses[x][y];
			if (house) {
				float distance = house->getDistance(centerX, centerY);
				if (distance <= range) {
					// La maison est dans le rayon, on l'ajoute à la liste ordonnée
					ordered_list.insert(std::make_pair(distance, house));
				}
			}
		}
	}

	// On transforme notre multimap en un vecteur trié
	vector<Models::House*> result;
	for (const auto& pair : ordered_list) {
		result.push_back(pair.second);
	}
	return result;
}

vector<Models::Tile*> LogicManager::getTilesInRange(int centerX, int centerY, int range) 
{
	vector<Models::Tile*> result;
	// On parcourt toutes les tiles via le cache de localisation
	int minX = centerX - range;
	int maxX = centerX + range;
	int minY = centerY - range;
	int maxY = centerY + range;

	// On ajuste les bornes pour qu'elles restent dans les limites de la ville
	if (minX < 0) minX = 0;
	if (maxX >= this->town->getSizeX()) maxX = this->town->getSizeX() - 1;
	if (minY < 0) minY = 0;
	if (maxY >= this->town->getSizeY()) maxY = this->town->getSizeY() - 1;

	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			Models::Tile* tile = this->town->getTileAt(x, y);
			if (tile) {
				float distance = tile->getDistance(centerX, centerY);
				if (distance <= range) {
					// La tile est dans le rayon, on l'ajoute à la liste
					result.push_back(tile);
				}
			}
		}
	}
	return result;
}

bool LogicManager::isValidLocation(float x, float y, float rotation, float sizeX, float sizeY)
{
	// On crée une Location temporaire pour vérifier les collisions
	Models::Location tempLocation(x, y, rotation, sizeX, sizeY);

	// On vérifie si la Location est dans les limites de la ville
	if (x - sizeX / 2 < 0 || x + sizeX / 2 >= this->town->getSizeX() ||
		y - sizeY / 2 < 0 || y + sizeY / 2 >= this->town->getSizeY()) {
		// La Location dépasse les limites de la ville
		return false;
	}

	// On définit les bornes de la zone à vérifier, avec la taille de la Location actuelle et la taille maximale des Locations
	float minX = x - (sizeX + Models::Location::getMaxSizeX()) / 2;
	float maxX = x + (sizeX + Models::Location::getMaxSizeX()) / 2;
	float minY = y - (sizeY + Models::Location::getMaxSizeY()) / 2;
	float maxY = y + (sizeY + Models::Location::getMaxSizeY()) / 2;

	// On ajuste les bornes pour qu'elles restent dans les limites de la ville
	if (minX < 0) minX = 0;
	if (maxX >= this->town->getSizeX()) maxX = this->town->getSizeX() - 1;
	if (minY < 0) minY = 0;
	if (maxY >= this->town->getSizeY()) maxY = this->town->getSizeY() - 1;

	// On parcourt uniquement les Locations dans la zone définie
	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			Models::Location* location = mapLocations[x][y];
			if (location) {
				if (tempLocation.collisionWith(*location)) {
					// Collision détectée
					return false;
				}
			}
		}
	}

	// Pas de collision détectée
	return true;
}

void LogicManager::updateCanHaveHouseAroundConstruction(Models::Location* location)
{
	// On définit les bornes de la zone à vérifier, avec la taille de la Location actuelle et la taille maximale des Locations
	float minX = location->getX() - (location->getSizeX() + Models::House::minSizeX) / 2;
	float maxX = location->getX() + (location->getSizeX() + Models::House::minSizeX) / 2;
	float minY = location->getY() - (location->getSizeY() + Models::House::minSizeY) / 2;
	float maxY = location->getY() + (location->getSizeY() + Models::House::minSizeY) / 2;
	// On ajuste les bornes pour qu'elles restent dans les limites de la ville
	if (minX < 0) minX = 0;
	if (maxX >= this->town->getSizeX()) maxX = this->town->getSizeX() - 1;
	if (minY < 0) minY = 0;
	if (maxY >= this->town->getSizeY()) maxY = this->town->getSizeY() - 1;
	// On parcourt uniquement les Tiles dans la zone définie
	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			Models::Tile* tile = this->town->getTileAt(x, y);
			if (tile) {
				tile->setCanHaveHouse(false);
			}
		}
	}
}

void LogicManager::updateCanHaveHouseAroundDestruction(Models::Location* location)
{
	// On définit les bornes de la zone à vérifier, avec la taille de la Location actuelle et la taille maximale des Locations
	float minX = location->getX() - (location->getSizeX() + Models::House::minSizeX) / 2;
	float maxX = location->getX() + (location->getSizeX() + Models::House::minSizeX) / 2;
	float minY = location->getY() - (location->getSizeY() + Models::House::minSizeY) / 2;
	float maxY = location->getY() + (location->getSizeY() + Models::House::minSizeY) / 2;
	// On ajuste les bornes pour qu'elles restent dans les limites de la ville
	if (minX < 0) 
		minX = 0;
	if (maxX >= this->town->getSizeX()) 
		maxX = this->town->getSizeX() - 1;
	if (minY < 0) 
		minY = 0;
	if (maxY >= this->town->getSizeY()) 
		maxY = this->town->getSizeY() - 1;

	// On parcourt uniquement les Tiles dans la zone définie
	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			Models::Tile* tile = this->town->getTileAt(x, y);
			if (tile) {
				// On met à jour la capacité de recevoir une maison de ce tile
				tile->updateCanHaveHouse();
			}
		}
	}
}

void LogicManager::addPossibleHouseLocation(Models::Tile* tile)
{
	if (std::find(possibleHouseLocations.begin(), possibleHouseLocations.end(), tile) == possibleHouseLocations.end()) {
		// La liste des emplacements possibles ne contient pas encore ce tile, on l'ajoute
		possibleHouseLocations.push_back(tile);
	}
}
void LogicManager::removePossibleHouseLocation(Models::Tile* tile)
{
	auto it = std::find(possibleHouseLocations.begin(), possibleHouseLocations.end(), tile);
	if (it != possibleHouseLocations.end()) {
		// La liste des emplacements possibles contient ce tile, on le retire
		possibleHouseLocations.erase(it);
	}
}

Models::Tile* LogicManager::pickPossibleHouseLocation()
{
	if (possibleHouseLocations.empty()) {
		return nullptr; // Pas d'emplacement possible
	}
	vector<Models::Tile*> candidates;
	float bestScore = 0.0f;

	// On parcourt les emplacements possibles pour trouver le meilleur pour une maison de base 
	for (Models::Tile* tile : possibleHouseLocations) {
		float score = tile->getAttractiveness(Models::Pop::Gueux);
		if (score > bestScore) {
			bestScore = score;
			candidates.clear();
			candidates.push_back(tile);
		}
		else if (score == bestScore) {
			candidates.push_back(tile);
		}
	}

	// On choisit un tile au hasard parmi les meilleurs candidats
	if (!candidates.empty()) {
		int index = rand() % candidates.size();
		return candidates[index];
	}

	return nullptr;
}