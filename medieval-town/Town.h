#pragma once
#include <string>
#include <vector>
#include "Family.h"

namespace Models
{
	// Ville dans laquelle se d�roule une partie
	class Town
	{
		public:
			Town(); // Constructeur par d�faut (�a fait plaisir au GameManager)
			Town(const std::string name);
			void startTown(); // Inititialisation du d�but de partie
			void logicTick(); // Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)

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

			// Les vecteurs ci-dessous contiennent les objets eux-m�mes, pas des pointeurs ou des r�f�rences. C'est donc ici qu'est g�r� leur cycle de vie.
			std::vector<Family> families; // Liste des familles dirigeantes de la ville
			std::vector<Building> buildings; // Liste des b�timents de la ville
			std::vector<Construction> constructions; // Liste des chantiers de construction de la ville
			int date; // Date actuelle de la ville (en jours depuis le d�but de la partie)
	};
}

