#pragma once
#include <string>
#include <vector>
#include "Family.h"

namespace Models
{
	// Ville dans laquelle se déroule une partie
	class Town
	{
		public:
			Town(const std::string& name);
			std::string getName() const;

			void addFamily(const Family& family);
			void removeFamily(const Family& family);
			std::vector<Family> getFamilies() const;

			void addBuilding(const Building& building);
			void removeBuilding(const Building& building);
			std::vector<Building> getBuildings() const;

			void addConstruction(const Construction& construction);
			void removeConstruction(const Construction& construction);
			std::vector<Construction> getConstructions() const;

		private:
			std::string name;
			std::vector<Family> families; // Liste des familles dirigeantes de la ville
			std::vector<Building> buildings; // Liste des bâtiments de la ville
			std::vector<Construction> constructions; // Liste des chantiers de construction de la ville
	};
}

