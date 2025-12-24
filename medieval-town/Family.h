#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <map>
#include "Resource.h"
using int32 = int32_t; // Match le type "int" d'Unreal Engine

namespace Models
{
	// Forward declarations pour éviter les dépendances circulaires
	class Building;
	class Construction;

	// Famille dirigeante de la ville, incarnée par un joueur ou par l'IA
	class Family
	{
	public:
		Family(const std::string name, const bool isAi);

		void logicTick(); // Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)

		int32 getId() const;
		void setId(int32 newId);
		std::string getName() const;
		bool getIsAi() const;
		int32 getGold() const;
		int32 getPrestige() const;
		void addGold(int32 amount);
		void addPrestige(int32 amount);
		void removeGold(int32 amount);
		void removePrestige(int32 amount);

		void addBuilding(Building* building);
		void removeBuilding(Building* building);
		void addConstruction(Construction* construction);
		void removeConstruction(Construction* construction);

		int32 getResource(Resource resource); // Récupère la quantité de la ressource donnée
		void addResource(Resource resource, int32 amount); // Ajoute une certaine quantité de la ressource donnée

	protected:
		int32 id = 0; // ID unique de la famille dans la ville
		bool isAi = false; // Indique si la famille est contrôlée par l'IA
		std::string name = ""; // Nom de la famille
		int32 gold = 0; // Quantité d'or possédée par la famille
		int32 prestige = 0; // Niveau de prestige de la famille
		std::vector<Building*> buildings; // Liste des bâtiments de la famille (en référence pour éviter les copies)
		std::vector<Construction*> constructions; // Liste des chantiers de construction de la famille (en référence pour éviter les copies)
		std::map<Resource, int32> resources = {}; // Ressources possédées par la famille
	};

}

