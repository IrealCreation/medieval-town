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
		// On regarde si la ville est attractive (si une case peut recevoir de la population)
		Tile* possibleHouseLocation = LogicManager::getInstance().pickPossibleHouseLocation();
		if (possibleHouseLocation != nullptr) {
			// La ville est attractive
			demographicPressure += 50; 
			// TODO: calculer la pression démographique en fonction de l'attractivité, de la population actuelle, etc.
			if (demographicPressure >= 100) { 
				// Assez de pression démographique pour accroitre la population

				int32 incomingPops = demographicPressure / 100; // Nombre de pops souhaitant s'installer en ville

				// 60% de chance d'essayer d'avoir une grande maison
				bool largeHouse = LogicManager::getInstance().randRange(0, 100) < 60;
				if (largeHouse) {
					// Vérifions que l'emplacement puisse accueillir une grande maison, sinon on mettra une petite maison
					if (!LogicManager::getInstance().isValidLocation(possibleHouseLocation->getX(), possibleHouseLocation->getY(), 0, 5, 8)) {
						largeHouse = false;
					}
				}

				if(largeHouse) {
					// On fait une grande maison
					// On vérifie que le nombre de pops entrants ne dépasse pas la capacité maximale de la maison
					int32 maxIncomingPops = House::getBaseCapacity(5, 8);
					if (incomingPops > maxIncomingPops) {
						incomingPops = maxIncomingPops;
					}
					LogicManager::getInstance().startConstructionHouse(possibleHouseLocation->getX(), possibleHouseLocation->getY(), 0, 5, 8, 1,
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
					LogicManager::getInstance().startConstructionHouse(possibleHouseLocation->getX(), possibleHouseLocation->getY(), 0, 4, 6, 1, 
						{ {Pop::Gueux, incomingPops}, {Pop::Bourgeois, 0}, {Pop::Noble, 0} }
					);
				}

				demographicPressure -= 100 * incomingPops;
			}
		}
		// TODO: faire spawn des maisons d'un niveau plus élevé si la ville est assez évoluée
		// TODO: évolution des maisons existantes

		// La liste des constructions peut changer pendant le tick (fin de construction), donc on en fait une copie avant de la parcourir
		vector<Construction*> constructionsCopy;
		for (const auto& construction : constructions) {
			constructionsCopy.push_back(construction.get());
		}

		// Tick des constructions
		for (const auto& construction : constructionsCopy) {
			construction->logicTick();
		}
		// Tick des bâtiments
		for (const auto& building : buildings) {
			building->logicTick();
		}
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
		return nullptr;
	}
}