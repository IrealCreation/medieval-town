#pragma once
#include <string>
#include <vector>
#include "Building.h"
#include "Construction.h"

namespace Models
{
	// Famille dirigeante de la ville, incarn�e par un joueur ou par l'IA
	class Family
	{
		public:
			Family(const std::string name);

			void LogicTick(); // Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)

			std::string getName() const;
			int getGold() const;
			int getPrestige() const;
			void addGold(int amount);
			void addPrestige(int amount);
			void removeGold(int amount);
			void removePrestige(int amount);

			void addBuilding(Building& building);
			void removeBuilding(Building& building);
			void addConstruction(Construction& construction);
			void removeConstruction(Construction& construction);

		protected:
			std::string name;
			int gold;
			int prestige;
			std::vector<Building&> buildings; // Liste des b�timents de la famille (en r�f�rence pour �viter les copies)
			std::vector<Construction&> constructions; // Liste des chantiers de construction de la famille (en r�f�rence pour �viter les copies)
	};

}

