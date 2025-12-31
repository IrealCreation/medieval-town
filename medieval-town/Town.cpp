#include "Town.h"
#include "Family.h"
#include "Service.h"
#include "Tile.h"
#include "LogicManager.h"
#include <iterator>
#include <algorithm>
#include <random>

namespace Models
{
	Town::Town(std::string name, int32 sizeX, int32 sizeY)
	{
		this->name = name;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->demographicPressure = 0;
	}

	void Town::startTown() {
		// Génération des tiles (le Tile 0,0 est en bas à gauche)
		for (int32 x = 0; x < sizeX; x++) {
			for (int32 y = 0; y < sizeY; y++) {
				mapTiles[x][y] = std::make_unique<Tile>(x, y);
			}
		}
	}

	void Town::logicTick()
	{
		// -- Passage d'un nouveau jour
		date++;

		// -- Pression démographique et éventuel accroissement de la population
		this->demographicGrowthTick();

		// La liste des constructions peut changer pendant le tick (fin de construction), donc on en fait une copie avant de la parcourir
		vector<Construction*> constructionsCopy;
		for (const auto& construction : constructions) {
			constructionsCopy.push_back(construction.get());
		}

		// Tick des constructions
		for (const auto& construction : constructionsCopy) {
			construction->logicTick();
		}
		// Tick des bâtiments : production
		for (int32 queue = 0; queue < 2; queue++) {
			// On itère sur les queues de production qui permettent de respecter l'ordre de production des bâtiments (ressources primaires d'abord, celles qui en découlent ensuite)
			for (const auto& building : buildings) {
				building->logicTick_production(queue);
			}
		}
		// Tick des bâtiments : services
		for (const auto& building : buildings) {
			building->logicTick_service();
		}
		// Tick des maisons
		for (const auto& house : houses) {
			house->logicTick();
		}
	}

	void Town::demographicGrowthTick() {

		int32 minimumAttractiveness = 0 - ServiceReceiver::getNumberOfServicesForPop(Pop::Gueux); // Seuil d'attractivité à dépasser pour que la croissance démographique puisse se faire

		// Trouvons la maison existante la plus attractive pouvant accueillir un nouvel habitant
		House* existingHouseCandidate = LogicManager::getInstance().getMostAttractiveHouse(minimumAttractiveness);
		// Trouvons l'emplacement le plus attractif pour construire une nouvelle maison
		Tile* newHouseCandidate = LogicManager::getInstance().getBestHouseLocation(minimumAttractiveness);

		int32 attractiveness = minimumAttractiveness; // Attractivité de l'emplacement retenu et de la ville
		bool newHouse = false; // True si on construit une nouvelle maison, false si on émigre dans une maison existante

		// Regardons qu'est-ce qui est le plus attractif
		if(existingHouseCandidate != nullptr) {
			attractiveness = existingHouseCandidate->getAttractiveness(Pop::Gueux);
		}
		if(newHouseCandidate != nullptr) {
			int32 newHouseAttractiveness = newHouseCandidate->getAttractiveness(Pop::Gueux);
			if (newHouseAttractiveness > attractiveness) {
				// L'emplacement pour une nouvelle maison est plus attractif que la meilleure maison existante
				attractiveness = newHouseAttractiveness;
				newHouse = true;
			}
		}

		// Si l'attractivité est restée à 0, pas de croissance à ce tick
		if (attractiveness == minimumAttractiveness) {
			return;
		}
		
		// Plus l'attractivité dépasse le seuil minimum, plus la pression démographique augmente (rappel : l'attractivité est un nombre négatif)
		demographicPressure += 100 * (minimumAttractiveness - attractiveness) * -1;

		if (demographicPressure >= 100) {
			// Assez de pression démographique pour accroitre la population

			int32 incomingPops = demographicPressure / 100; // Nombre de pops souhaitant s'installer en ville

			if(newHouse) {
				// On construit une nouvelle maison
				incomingPops = this->demographicGrowth_newHouse(newHouseCandidate, incomingPops);
			}
			else {
				// On agrandit une maison existante
				incomingPops = this->demographicGrowth_existingHouse(existingHouseCandidate, incomingPops);
			}

			// On diminue la pression démographique de 100 par nouvel habitant
			demographicPressure -= 100 * incomingPops;
		}
	}

	int32 Town::demographicGrowth_newHouse(Tile* newHouseLocation, int32 incomingPops) {
		// 60% de chance d'essayer d'avoir une grande maison
		bool largeHouse = LogicManager::getInstance().randRange(0, 100) < 60;
		if (largeHouse) {
			// Vérifions que l'emplacement puisse accueillir une grande maison, sinon on mettra une petite maison
			if (!LogicManager::getInstance().isValidLocation(newHouseLocation->getX(), newHouseLocation->getY(), 0, 5, 9)) {
				largeHouse = false;
			}
		}

		if (largeHouse) {
			// On fait une grande maison
			// On vérifie que le nombre de pops entrants ne dépasse pas la capacité maximale de la maison
			int32 maxIncomingPops = House::getBaseCapacity(5, 9);
			if (incomingPops > maxIncomingPops) {
				incomingPops = maxIncomingPops;
			}
			LogicManager::getInstance().startConstructionHouse(newHouseLocation->getX(), newHouseLocation->getY(), 0, 5, 9, 1,
				{ {Pop::Gueux, incomingPops}, {Pop::Bourgeois, 0}, {Pop::Noble, 0} }
			);
		}
		else {
			// On fait une petite maison
			// On vérifie que le nombre de pops entrants ne dépasse pas la capacité maximale de la maison
			int32 maxIncomingPops = House::getBaseCapacity(4, 6);
			if (incomingPops > maxIncomingPops) {
				incomingPops = maxIncomingPops;
			}
			LogicManager::getInstance().startConstructionHouse(newHouseLocation->getX(), newHouseLocation->getY(), 0, 4, 7, 1,
				{ {Pop::Gueux, incomingPops}, {Pop::Bourgeois, 0}, {Pop::Noble, 0} }
			);
		}

		return incomingPops;

		// TODO: faire spawn des maisons d'un niveau plus élevé si la ville est assez évoluée
	}

	int32 Town::demographicGrowth_existingHouse(House* house, int32 incomingPops) {
		// Vérifions les capacités de la maison
		if(incomingPops >= house->getFreePop(Pop::Gueux)) {
			incomingPops = house->getFreePop(Pop::Gueux);
		}
		house->addPop(Pop::Gueux, incomingPops);
		LogicManager::getInstance().log("La maison existante en " + std::to_string(house->getX()) + "," + std::to_string(house->getY()) + " accueille " + std::to_string(incomingPops) + " nouveaux habitants.");
		return incomingPops;
	}

	std::string Town::getName() const
	{
		return name;
	}
	int32 Town::getSizeX() const
	{
		return sizeX;
	}
	int32 Town::getSizeY() const
	{
		return sizeY;
	}
	int32 Town::getDate() const
	{
		return date;
	}

	void Town::addBuilding(unique_ptr<Building> building)
	{
		buildings.push_back(std::move(building));
	}
	void Town::removeBuilding(Building* building)
	{
		/*
		// On utilise std::find pour trouver le bâtiment dans le vecteur
		auto it = std::find(buildings.begin(), buildings.end(), building);
		// On retire le bâtiment du vecteur
		buildings.erase(it);
		*/
	}

	void Town::addConstruction(unique_ptr<Construction> construction)
	{
		constructions.push_back(std::move(construction));
	}
	void Town::removeConstruction(Construction* construction)
	{
		// On récupère l'itérateur vers l'unique_ptr correspondant au raw pointer
		auto it = std::find_if(constructions.begin(), constructions.end(), [&construction](const unique_ptr<Construction>& c) {
			return c.get() == construction;
		});
		constructions.erase(it);
	}

	int32 Town::addFamily(unique_ptr<Family> family)
	{
		// On ajoute la famille à la fin du vecteur
		families.push_back(std::move(family));
		// On renvoie l'index (ID) de la famille dans la liste, à savoir la taille du vecteur - 1
		return families.size() - 1;
	}
	vector<Family*> Town::getFamilies() {
		// On transforme notre tableau de unique_ptr en un tableau de raw pointers
		std::vector<Family*> tmp_families;
		std::transform(this->families.begin(), this->families.end(),
			std::back_inserter(tmp_families),
			[](const std::unique_ptr<Family>& mon_in) { return mon_in.get(); });
		return tmp_families;
		// TODO: typiquement le genre de fonction qui pourrait être un template
	}
	Family* Town::getFamily(int32 id) {
		if (id >= 0 && id < families.size()) {
			return families[id].get();
		}
		return nullptr;
	}

	void Town::addHouse(unique_ptr<House> house)
	{
		houses.push_back(std::move(house));
	}
	void Town::removeHouse(House* house)
	{
		// On récupère l'itérateur vers l'unique_ptr correspondant au raw pointer
		auto it = std::find_if(houses.begin(), houses.end(), [&house](const unique_ptr<House>& h) {
			return h.get() == house;
		});
		houses.erase(it);
	}
	vector<House*> Town::getHouses() {
		// On transforme notre tableau de unique_ptr en un tableau de raw pointers
		std::vector<House*> tmp_houses;
		std::transform(this->houses.begin(), this->houses.end(),
			std::back_inserter(tmp_houses),
			[](const std::unique_ptr<House>& mon_in) { return mon_in.get(); });
		return tmp_houses;
	}

	Tile* Town::getTileAt(int32 x, int32 y) {
		if (mapTiles.find(x) != mapTiles.end() && mapTiles[x].find(y) != mapTiles[x].end()) {
			return mapTiles[x][y].get();
		}
		LogicManager::getInstance().log("Town::getTileAt : coordonnées invalides (" + std::to_string(x) + "," + std::to_string(y) + ")");
		return nullptr;
	}

	int32 Town::getResource(Resource resource)
	{
		int32 total = 0;
		// On additionne les ressources de chaque famille
		for (const auto& family : families) {
			total += family->getResource(resource);
		}
		return total;
	}

	void Town::takeResource(Resource resource, int32 amount, Family taker)
	{
		// TODO: prélever la ressource aux familles qui la possédent de manière équilibrée
		// TODO: implémenter le paiement
		return;
	}
}