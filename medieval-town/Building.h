#pragma once
#include "BuildingType.h"
#include "Location.h"
#include "Family.h"

namespace Models
{
	class Building : public Location
	{
	public:
		Building(const BuildingType& type, const Location& location, Family* family);
		void logicTick(); // Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)

		std::string getName();
		void setName(const std::string& name);

	private:
		const BuildingType& type; // Un building ne change jamais de type, donc on le stocke par r�f�rence et en const
		Family* family; // Famille propri�taire du b�timent ; nullptr si pas de propri�taire, donc on le stocke par pointeur
		std::string name; // Nom personnalis� du b�timent (nom de son BuildingType sinon)
		int dateCreation; // Date de cr�ation du b�timent (fin du chantier de construction)
	};
}

