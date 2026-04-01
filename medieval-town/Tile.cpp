#include "Tile.h"
#include "House.h"
#include "LogicManager.h"
#include "Town.h"

namespace Models
{
	Tile::Tile(int32 x, int32 y) : Location(x, y, 0), ServiceReceiver()
	{
		// Au début de la partie, toutes les tuiles peuvent recevoir une maison, sauf celles situées trop près du bord de la map
		if (x < House::minSizeX / 2 
			|| y < House::minSizeY / 2 
			|| x > LogicManager::getInstance().getTown()->getSizeX() - House::minSizeX / 2 
			|| y > LogicManager::getInstance().getTown()->getSizeY() - House::minSizeY / 2) {
			canHaveHouse = false;
		}
		else {
			canHaveHouse = true;
		}
	}

	bool Tile::getCanHaveHouse() const {
		return canHaveHouse;
	}

	void Tile::addNoHouseCause(Location* location) {
		if (std::find(noHouseCauses.begin(), noHouseCauses.end(), location) == noHouseCauses.end()) {
			noHouseCauses.push_back(location);
			setCannotHaveHouse();
		}
	}

	void Tile::removeNoHouseCause(Location* location) {
		auto it = std::find(noHouseCauses.begin(), noHouseCauses.end(), location);
		if (it != noHouseCauses.end()) {
			noHouseCauses.erase(it);
			if (noHouseCauses.empty()) {
				setCanHaveHouse();
			}
		}
	}

	void Tile::setCannotHaveHouse() {
		if (canHaveHouse == false)
			return; // Pas de changement
		LogicManager::getInstance().removePossibleHouseLocation(this);
		canHaveHouse = false;
	}
	void Tile::setCanHaveHouse() {
		if (canHaveHouse == true)
			return; // Pas de changement
		canHaveHouse = true;
		// On ajoute ce tile à la liste des emplacements possibles pour une maison si son attractivité est supérieure au minimum
		if (getAttractiveness(Pop::Gueux) > 0 - ServiceReceiver::getNumberOfServicesForPop(Pop::Gueux)) {
			LogicManager::getInstance().addPossibleHouseLocation(this);
		}
	}

	void Tile::updateAttractiveness() {
		int32 minimumAttractiveness = 0 - ServiceReceiver::getNumberOfServicesForPop(Pop::Gueux);

		int32 attractivenessBefore = getAttractiveness(Pop::Gueux);

		// On appelle la méthode parente pour mettre à jour l'attractivité en fonction des services disponibles
		ServiceReceiver::updateAttractiveness();

		int32 attractivenessAfter = getAttractiveness(Pop::Gueux);

		// Si l'attractivité est passée de plus de du minimum au minimum...
		if (attractivenessBefore > minimumAttractiveness && attractivenessAfter <= minimumAttractiveness) {
			// ... on retire ce tile de la liste des emplacements possibles pour une maison
			LogicManager::getInstance().removePossibleHouseLocation(this);
		}
		// Si l'attractivité est passée du minimum à plus du minimum, et que le tile peut recevoir une maison...
		else if (attractivenessBefore <= minimumAttractiveness && attractivenessAfter > minimumAttractiveness && getCanHaveHouse()) {
			// ... on ajoute ce tile à la liste des emplacements possibles pour une maison
			LogicManager::getInstance().addPossibleHouseLocation(this);
		}
	}
}