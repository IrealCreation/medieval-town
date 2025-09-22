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

// Pourquoi est-ce qu'il en a besoin pour les vector<unique_ptr<Construction>>, mais pas de Family.h ?
#include "Building.h";
#include "Construction.h";
#include "House.h";
#include "Tile.h";

namespace Models
{
	// Forward declarations pour �viter les d�pendances circulaires
	class Family;
	//class Building;
	class BuildingType;
	class Location;
	//class Construction;
	
	// Ville dans laquelle se d�roule une partie
	class Town
	{
		public:
			Town(const string name, int sizeX, int sizeY);
			void startTown(); // Inititialisation du d�but de partie
			void logicTick(); // Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)

			string getName() const;
			int getDate() const;

			int getSizeX() const;
			int getSizeY() const;

			void addFamily(unique_ptr<Family> family);
			vector<Family*> getFamilies();

			void addConstruction(unique_ptr<Construction> construction);
			void removeConstruction(Construction* construction);

			void addBuilding(unique_ptr<Building> building);
			void removeBuilding(Building* building);

			void addHouse(unique_ptr<House> house);
			void removeHouse(House* house);
			vector<House*> getHouses();

			Tile* getTileAt(int x, int y); // Retourne un raw pointer vers la Tile � la position donn�e ; nullptr si pas de Tile (coordonn�es invalides)

		protected:
			string name;
			int sizeX; // Taille de la ville en X
			int sizeY; // Taille de la ville en Y
			// On triche un peu : la taille de la ville est de 1 case sup�rieure, car il y a la Tile 0,0

			// Les vecteurs ci-dessous contiennent des unique_ptr car Town g�re leur cycle de vie ; ils seront communiqu�s sous forme de raw pointers 
			vector<unique_ptr<Family>> families; // Liste des familles dirigeantes de la ville
			vector<unique_ptr<Construction>> constructions; // Liste des chantiers de construction de la ville
			vector<unique_ptr<Building>> buildings; // Liste des b�timents de service de la ville
			vector<unique_ptr<House>> houses; // Liste des maisons d'habitation de la ville
			int date; // Date actuelle de la ville (en jours depuis le d�but de la partie)

			// Grille des Tiles [x => [y => Tile]]
			map<int, map<int, unique_ptr<Tile>>> mapTiles;
	};
}

