#include "LogicManager.h"
#include "Town.h"
#include "BuildingType.h"
#include "Building.h"
#include "Family.h"
#include "Location.h"
#include "Construction.h"
#include "ConstructionBuilding.h"
#include "ConstructionHouse.h"
#include <iostream> // Pour le log()

using std::string;
using std::make_unique;
using std::make_shared;

LogicManager::LogicManager() {}

LogicManager& LogicManager::getInstance()
{
	return LogicManager::instance;
}

void LogicManager::startGame()
{
	// Création de la ville
	this->town = make_unique<Models::Town>("Lorrez-le-Bocage");
	town->startTown();

	// Création des familles
	unique_ptr<Models::Family> family1 = make_unique<Models::Family>("Salviati");
	this->town->addFamily(std::move(family1));
	unique_ptr<Models::Family> family2 = make_unique<Models::Family>("Legrand");
	this->town->addFamily(std::move(family2));
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

void LogicManager::log(string message) {
	std::cout << message << "\n";
}

Models::Town* LogicManager::getTown()
{
	return this->town.get();
}

void LogicManager::startConstructionBuilding(const Models::BuildingType& type, Models::Family* family, int x, int y, int rotation)
{
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

	// Enfin, on bouge le unique_ptr dans Town qui en a désormais la charge
	town->addConstruction(std::move(construction));
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
	// On ajoute le Building dans la famille (s'il en a une)
	if (family != nullptr)
		family->addBuilding(building.get());
	// On déplace le pointeur unique dans la Town
	town->addBuilding(std::move(building));

	// UE : spawn l'objet Building
}

void LogicManager::startConstructionHouse(int x, int y, int rotation, int sizeX, int sizeY, int niveau)
{
	// Création de la Construction
	unique_ptr<Models::ConstructionHouse> construction = make_unique<Models::ConstructionHouse>(x, y, rotation, sizeX, sizeY, niveau);
	// On log l'événement
	this->log("Debut de la construction d'une maison a " + std::to_string(construction->getX()) + " ; " + std::to_string(construction->getY()));
	// On ajoute la Construction dans le cache de localisation
	mapLocations[construction->getX()][construction->getY()] = construction.get();
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
	// On déplace le pointeur unique dans la Town
	town->addHouse(std::move(house));
	// UE : spawn l'objet House
}

