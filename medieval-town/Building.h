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
		void logicTick(); // Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)

		std::string getName();
		void setName(const std::string& name);

	private:
		const BuildingType& type; // Un building ne change jamais de type, donc on le stocke par référence et en const
		Family* family; // Famille propriétaire du bâtiment ; nullptr si pas de propriétaire, donc on le stocke par pointeur
		std::string name; // Nom personnalisé du bâtiment (nom de son BuildingType sinon)
		int dateCreation; // Date de création du bâtiment (fin du chantier de construction)
	};
}

