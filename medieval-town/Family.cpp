#include "Family.h"
#include "Building.h"
#include "Construction.h"

namespace Models
{
	Family::Family(const std::string name)
		: name(name), gold(0), prestige(0) {}
	void Family::logicTick() {
		// Logique de progression du jeu pour la famille, par exemple, mise à jour des ressources
	}
	std::string Family::getName() const {
		return name;
	}
	int Family::getGold() const {
		return gold;
	}
	int Family::getPrestige() const {
		return prestige;
	}
	void Family::addGold(int amount) {
		gold += amount;
	}
	void Family::addPrestige(int amount) {
		prestige += amount;
	}
	void Family::removeGold(int amount) {
		gold -= amount;
	}
	void Family::removePrestige(int amount) {
		prestige -= amount;
	}
	void Family::addBuilding(Building& building) {
		buildings.push_back(building);
	}
	void Family::removeBuilding(Building* building) {
		auto it = std::remove(buildings.begin(), buildings.end(), building);
		buildings.erase(it, buildings.end());
	}
	void Family::addConstruction(Construction& construction) {
		constructions.push_back(construction);
	}
	void Family::removeConstruction(Construction& construction) {
		auto it = std::remove(constructions.begin(), constructions.end(), construction);
		constructions.erase(it, constructions.end());
	}
} // namespace Models