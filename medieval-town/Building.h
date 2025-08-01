#pragma once
#include "BuildingType.h"
#include "Location.h"

namespace Models
{
	class Building
	{
	public:
		Building(const BuildingType& type, const Location& location);

	private:
		BuildingType type;
		std::string name; // Nom personnalisé du bâtiment (nom de son BuildingType sinon)
		Location location; // Emplacement du bâtiment dans la ville
	};
}

