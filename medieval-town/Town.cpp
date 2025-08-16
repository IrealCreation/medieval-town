#include "Town.h"

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

	void Town::addBuilding(const Building building)
	{
		// On ajoute à la fin du vecteur
		buildings.push_back(building);
	}
	void Town::removeBuilding(const Building& building)
	{
		// On utilise std::find pour trouver le bâtiment dans le vecteur
		auto it = std::find(buildings.begin(), buildings.end(), building);
		// On retire le bâtiment du vecteur
		buildings.erase(it);
	}
	std::vector<Building> Town::getBuildings() const
	{
		return buildings;
	}

	void Town::addConstruction(const Construction construction)
	{
		constructions.push_back(construction);
	}
	void Town::removeConstruction(const Construction* construction)
	{
		auto it = std::find(constructions.begin(), constructions.end(), construction);
		constructions.erase(it);
	}
	std::vector<Construction> Town::getConstructions() const
	{
		return constructions;
	}

	void Town::addFamily(const Family family)
	{
		families.push_back(family);
	}
	void Town::removeFamily(const Family& family)
	{
		auto it = std::find(families.begin(), families.end(), family);
		families.erase(it);
	}
	std::vector<Family> Town::getFamilies() const
	{
		return families;
	}
}