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
		std::string name; // Nom personnalis� du b�timent (nom de son BuildingType sinon)
		Location location; // Emplacement du b�timent dans la ville
	};
}

