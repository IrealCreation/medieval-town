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
		Family* family; // Famille propri�taire du b�timent (peut �tre nullptr si pas de propri�taire)
		std::string name; // Nom personnalis� du b�timent (nom de son BuildingType sinon)
		int dateCreation; // Date de cr�ation du b�timent (fin du chantier de construction)
	};
}

