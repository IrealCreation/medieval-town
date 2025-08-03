#pragma once
#include "BuildingType.h"
#include "Location.h"

namespace Models
{
	class Building : public Location
	{
	public:
		Building(const BuildingType& type, const Location& location);
		std::string getName();
		void setName(const std::string& name);

	private:
		BuildingType type;
		std::string name; // Nom personnalisé du bâtiment (nom de son BuildingType sinon)
	};
}

