#include "Town.h"
//#include "BuildingType.h"
//#include "Building.h"
//#include "Construction.h"
#include "Family.h"
//#include "Location.h"
#include <iterator>
#include <algorithm>

namespace Models
{
	Town::Town()
	{
		name = "Default";
		date = 0; // Initialisation de la date à 0
	}
	Town::Town(std::string newName)
	{
		Town();
		name = newName;
	}

	void Town::startTown() {

	}

	void Town::logicTick()
	{
		// Passage d'un nouveau jour
		date++;

		// Tick des constructions
		for (const auto& construction : constructions) {
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
	}
}