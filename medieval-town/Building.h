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
		std::string getName();
		void setName(const std::string& name);

	private:
		BuildingType type;
		Family* family; // Famille propriétaire du bâtiment (peut être nullptr si pas de propriétaire)
		std::string name; // Nom personnalisé du bâtiment (nom de son BuildingType sinon)
		int dateCreation; // Date de création du bâtiment (fin du chantier de construction)
	};
}

