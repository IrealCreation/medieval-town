#pragma once
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <memory>
#include <map>
using std::unique_ptr;
using std::shared_ptr;
using std::map;
#include <cstdint>
using int32 = uint32_t; // Match le type "int" d'Unreal Engine

// Pourquoi est-ce qu'il en a besoin pour les vector<unique_ptr<Construction>>, mais pas de Family.h ?
#include "Building.h"
#include "Construction.h"
#include "House.h"
#include "Tile.h"

namespace Models
{
	// Forward declarations pour éviter les dépendances circulaires
	class Family;
	//class Building;
	class BuildingType;
	class Location;
	//class Construction;
	
	// Ville dans laquelle se déroule une partie
	class Town
	{
		public:
			Town(const string name, int32 sizeX, int32 sizeY);
			void startTown(); // Inititialisation du début de partie
			void logicTick(); // Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)

			string getName() const;
			int32 getDate() const;

			int32 getSizeX() const;
			int32 getSizeY() const;

			// Ajoute une famille à la ville ; retourne son index (ID) dans la liste des familles
			int32 addFamily(unique_ptr<Family> family);
			vector<Family*> getFamilies();
			Family* getFamily(int32 id);

			void addConstruction(unique_ptr<Construction> construction);
			void removeConstruction(Construction* construction);

			void addBuilding(unique_ptr<Building> building);
			void removeBuilding(Building* building);

			void addHouse(unique_ptr<House> house);
			void removeHouse(House* house);
			vector<House*> getHouses();

			Tile* getTileAt(int32 x, int32 y); // Retourne un raw pointer vers la Tile à la position donnée ; nullptr si pas de Tile (coordonnées invalides)

		protected:
			string name = ""; // Nom de la ville
			int32 sizeX = 0; // Taille de la ville en X
			int32 sizeY = 0; // Taille de la ville en Y
			// On triche un peu : la taille de la ville est de 1 case supérieure, car il y a la Tile 0,0

			int32 date = 1; // Date actuelle de la ville (en jours depuis le début de la partie)
			int32 demographicPressure = 100; // Pression démographique actuelle, accumulée à chaque tick et déclenche l'accroissement de la population par la construction ou l'aggrandissement de maisons quand un seuil est atteint. On commence avec une pression initiale élevée pour immédiatement avoir de nouvelles maisons dès que des emplacements sont attractifs.

			void demographicGrowthTick(); // Gère l'éventuelle croissance démographique de la ville à chaque tick (appelé depuis LogicTick)
			int32 demographicGrowth_newHouse(Tile* newHouseLocation, int32 incomingPops); // Gère la construction d'une nouvelle maison d'habitation (appelé depuis demographicGrowthTick). Retourne la quantité de nouveaux habitants prévus dans la nouvelle maison
			int32 demographicGrowth_existingHouse(House* house, int32 incomingPops); // Gère l'agrandissement d'une maison existante (appelé depuis demographicGrowthTick). Retourne la quantité de nouveaux habitants

			// Les vecteurs ci-dessous contiennent des unique_ptr car Town gère leur cycle de vie ; ils seront communiqués sous forme de raw pointers 
			vector<unique_ptr<Family>> families; // Liste des familles dirigeantes de la ville
			vector<unique_ptr<Construction>> constructions; // Liste des chantiers de construction de la ville
			vector<unique_ptr<Building>> buildings; // Liste des bâtiments de service de la ville
			vector<unique_ptr<House>> houses; // Liste des maisons d'habitation de la ville

			// Grille des Tiles [x => [y => Tile]]
			map<int32, map<int32, unique_ptr<Tile>>> mapTiles;
	};
}

