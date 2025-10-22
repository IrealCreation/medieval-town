#pragma once
#include <string>
#include <vector>
#include "Location.h" // Classe parent : on doit inclure son header

namespace Models
{
	// Forward declarations pour éviter les dépendances circulaires
	class Family;
	class BuildingType;
	class House;
	class Tile;

	// Bâtiment prodiguant des services aux alentours. C'est un lieu (Location) qui a un type (BuildingType) et éventuellement une famille propriétaire (Family)
	class Building : public Location
	{
	public:
		Building(const BuildingType& type, Family* family, float x, float y, float rotation);
		void logicTick(); // Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)

		std::string getName();
		void setName(const std::string& name);

		const BuildingType& getType() const; // Retourne le type du bâtiment

		Family* getFamily() const; // Retourne la famille propriétaire du bâtiment ; nullptr si pas de propriétaire

		void changeCapacityUsed(int delta); // Change la capacité utilisée du bâtiment de delta (positif ou négatif)

		std::vector<House*> getHousesServed() const; // Retourne la liste des maisons desservies par ce bâtiment
		void removeHouseServed(House* house); // Retire une maison desservie par ce bâtiment

		std::vector<Tile*> getMarginalTilesServed() const; // Retourne la liste des tuiles desservies par ce bâtiment

		void updateServed(); // Met à jour la liste des emplacements (House et Tiles) desservis par ce bâtiment
		void setMustUpdateServed(); // Indique que la liste des emplacements (House et Tiles) desservis doit être mise à jour au prochain tick

	private:
		const BuildingType& type; // Un building ne change jamais de type, donc on le stocke par référence et en const
		Family* family; // Famille propriétaire du bâtiment ; nullptr si pas de propriétaire, donc on le stocke par pointeur
		std::string name; // Nom personnalisé du bâtiment (nom de son BuildingType sinon)
		int dateCreation; // Date de création du bâtiment (fin du chantier de construction)
		int capacityUsed; // Capacité actuellement utilisée (nombre de pops servies)

		std::vector<House*> housesServed; // Maisons desservies par ce bâtiment
		bool mustUpdateServed = true; // Indique si la liste des emplacements (House et Tiles) desservis doit être mise à jour au prochain tick

		std::vector<House*> marginalHousesServed; // Maisons pouvant accueillir un habitant de plus servi par ce bâtiment
		std::vector<Tile*> marginalTilesServed; // Tuiles pouvant accueillir un habitant de plus servi par ce bâtiment
	};
}

