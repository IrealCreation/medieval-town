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

	// B�timent prodiguant des services aux alentours. C'est un lieu (Location) qui a un type (BuildingType) et �ventuellement une famille propri�taire (Family)
	class Building : public Location
	{
	public:
		Building(const BuildingType& type, Family* family, float x, float y, float rotation);
		void logicTick(); // Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)

		std::string getName();
		void setName(const std::string& name);

		void updateHousesServed(); // Met � jour la liste des maisons desservies par ce b�timent

	private:
		const BuildingType& type; // Un building ne change jamais de type, donc on le stocke par r�f�rence et en const
		Family* family; // Famille propri�taire du b�timent ; nullptr si pas de propri�taire, donc on le stocke par pointeur
		std::string name; // Nom personnalis� du b�timent (nom de son BuildingType sinon)
		int dateCreation; // Date de cr�ation du b�timent (fin du chantier de construction)

		std::vector<House*> housesServed; // Maisons desservies par ce b�timent
	};
}

