#include "Family.h"
#include "Building.h"
#include "Construction.h"

namespace Models
{
	Family::Family(const std::string name, const bool isAi)
		: name(name), isAi(isAi), gold(1000), prestige(100) {}

	void Family::logicTick() {
		// Logique de progression du jeu pour la famille, par exemple, mise à jour des ressources
	}
	int32 Family::getId() const {
		return id;
	}
	void Family::setId(int32 newId) {
		id = newId;
	}
	std::string Family::getName() const {
		return name;
	}
	bool Family::getIsAi() const {
		return isAi;
	}
	int32 Family::getGold() const {
		return gold;
	}
	int32 Family::getPrestige() const {
		return prestige;
	}
	void Family::addGold(int32 amount) {
		gold += amount;
	}
	void Family::addPrestige(int32 amount) {
		prestige += amount;
	}
	void Family::removeGold(int32 amount) {
		gold -= amount;
	}
	void Family::removePrestige(int32 amount) {
		prestige -= amount;
	}
	void Family::addBuilding(Building* building) {
		buildings.push_back(building);
	}
	void Family::removeBuilding(Building* building) {
		auto it = std::remove(buildings.begin(), buildings.end(), building);
		buildings.erase(it, buildings.end());
	}
	void Family::addConstruction(Construction* construction) {
		constructions.push_back(construction);
	}
	void Family::removeConstruction(Construction* construction) {
		auto it = std::remove(constructions.begin(), constructions.end(), construction);
		constructions.erase(it, constructions.end());
	}
} // namespace Models