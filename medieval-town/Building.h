#pragma once
#include <string>
#include <vector>
#include "Location.h" // Classe parent : on doit inclure son header

namespace Models
{
	// Forward declarations pour �viter les d�pendances circulaires
	class Family;
	class BuildingType;
	class House;
	class Tile;

	// B�timent prodiguant des services aux alentours. C'est un lieu (Location) qui a un type (BuildingType) et �ventuellement une famille propri�taire (Family)
	class Building : public Location
	{
	public:
		Building(const BuildingType& type, Family* family, float x, float y, float rotation);
		void logicTick(); // Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)

		std::string getName();
		void setName(const std::string& name);

		const BuildingType& getType() const; // Retourne le type du b�timent

		Family* getFamily() const; // Retourne la famille propri�taire du b�timent ; nullptr si pas de propri�taire

		void changeCapacityUsed(int delta); // Change la capacit� utilis�e du b�timent de delta (positif ou n�gatif)

		std::vector<House*> getHousesServed() const; // Retourne la liste des maisons desservies par ce b�timent
		void removeHouseServed(House* house); // Retire une maison desservie par ce b�timent

		std::vector<Tile*> getMarginalTilesServed() const; // Retourne la liste des tuiles desservies par ce b�timent

		void updateServed(); // Met � jour la liste des emplacements (House et Tiles) desservis par ce b�timent
		void setMustUpdateServed(); // Indique que la liste des emplacements (House et Tiles) desservis doit �tre mise � jour au prochain tick

	private:
		const BuildingType& type; // Un building ne change jamais de type, donc on le stocke par r�f�rence et en const
		Family* family; // Famille propri�taire du b�timent ; nullptr si pas de propri�taire, donc on le stocke par pointeur
		std::string name; // Nom personnalis� du b�timent (nom de son BuildingType sinon)
		int dateCreation; // Date de cr�ation du b�timent (fin du chantier de construction)
		int capacityUsed; // Capacit� actuellement utilis�e (nombre de pops servies)

		std::vector<House*> housesServed; // Maisons desservies par ce b�timent
		bool mustUpdateServed = true; // Indique si la liste des emplacements (House et Tiles) desservis doit �tre mise � jour au prochain tick

		std::vector<House*> marginalHousesServed; // Maisons pouvant accueillir un habitant de plus servi par ce b�timent
		std::vector<Tile*> marginalTilesServed; // Tuiles pouvant accueillir un habitant de plus servi par ce b�timent
	};
}

