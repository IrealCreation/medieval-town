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

	void Town::logicTick()
	{
		// Passage d'un nouveau jour
		date++;

		// TODO: tick des constructions, buildings, families
	}

	std::string Town::getName() const
	{
		return name;
	}
	int Town::getDate() const
	{
		return date;
	}

	void Town::addBuilding(const unique_ptr<Building> building)
	{
		//buildings.push_back(std::move(building));
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

	void Town::addConstruction(const unique_ptr<Construction> construction)
	{
		//constructions.push_back(std::move(construction));
	}
	void Town::removeConstruction(Construction* construction)
	{
		/*
		auto it = std::find(constructions.begin(), constructions.end(), construction);
		constructions.erase(it);
		*/
	}

	void Town::addFamily(const unique_ptr<Family> family)
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