#include "Town.h"
#include "Family.h"
#include "Service.h"
#include "Tile.h"
#include <iterator>
#include <algorithm>

namespace Models
{
	Town::Town(std::string name, int sizeX, int sizeY)
	{
		this->name = name;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
	}

	void Town::startTown() {
		// Génération des tiles (le Tile 0,0 est en bas à gauche)
		for (int x = 0; x < sizeX; x++) {
			for (int y = 0; y < sizeY; y++) {
				mapTiles[x][y] = std::make_unique<Tile>(x, y);
			}
		}
	}

	void Town::logicTick()
	{
		// Passage d'un nouveau jour
		date++;

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
	int Town::getSizeX() const
	{
		return sizeX;
	}
	int Town::getSizeY() const
	{
		return sizeY;
	}
	int Town::getDate() const
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

	void Town::addFamily(unique_ptr<Family> family)
	{
		families.emplace_back(std::move(family));
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

	Tile* Town::getTileAt(int x, int y) {
		if (mapTiles.find(x) != mapTiles.end() && mapTiles[x].find(y) != mapTiles[x].end()) {
			return mapTiles[x][y].get();
		}
		return nullptr;
	}
}