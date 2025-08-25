#include "Building.h"
#include "BuildingType.h"
#include "Family.h"

namespace Models {
	Building::Building(const BuildingType& type, Family* family, float x, float y, float rotation)
		: Location(x, y, rotation), type(type), family(family), name(type.getName()), dateCreation(0) {}

	void Building::logicTick() {
		
	}

	std::string Building::getName() {
		return name;
	}

	void Building::setName(const std::string& name) {
		this->name = name;
	}
} // namespace Models