#include "Building.h"
#include "BuildingType.h"
#include "Family.h"

namespace Models {
	Building::Building(const BuildingType& type, Family* family, float x, float y, float rotation)
		: Location(x, y, rotation), type(type), family(family), name(type.getName()), dateCreation(0) {}

	void Building::logicTick() {
		// TODO: calculer les effets du bâtiment en fonction des populations servies

		if (family) {
			// Le bâtiment a une famille propriétaire
			// DEBUG: on utilise le coût d'entretien comme gain d'or pour la famille
			family->addGold(type.getGoldMaintenanceCost());
		}
	}

	std::string Building::getName() {
		return name;
	}

	void Building::setName(const std::string& name) {
		this->name = name;
	}
} // namespace Models