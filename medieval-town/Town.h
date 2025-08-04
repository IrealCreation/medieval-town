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
			Town(); // Constructeur par défaut (ça fait plaisir au GameManager)
			Town(const std::string name);
			void startTown(); // Inititialisation du début de partie
			void logicTick(); // Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)

			std::string getName() const;
			int getDate() const;

			void addFamily(const Family family);
			void removeFamily(const Family& family);
			std::vector<Family> getFamilies() const;

			void addBuilding(const Building building);
			void removeBuilding(const Building& building);
			std::vector<Building> getBuildings() const;

			void addConstruction(const Construction construction);
			void removeConstruction(const Construction& construction);
			std::vector<Construction> getConstructions() const;

		private:
			std::string name;

			// Les vecteurs ci-dessous contiennent les objets eux-mêmes, pas des pointeurs ou des références. C'est donc ici qu'est géré leur cycle de vie.
			std::vector<Family> families; // Liste des familles dirigeantes de la ville
			std::vector<Building> buildings; // Liste des bâtiments de la ville
			std::vector<Construction> constructions; // Liste des chantiers de construction de la ville
			int date; // Date actuelle de la ville (en jours depuis le début de la partie)
	};
}

