#include "Tile.h"
#include "House.h"
#include "LogicManager.h"
#include "Town.h"

namespace Models
{
	Tile::Tile(int x, int y) : Location(x, y, 0) 
	{
		// Au d�but de la partie, toutes les tuiles peuvent recevoir une maison
		canHaveHouse = true;
	}

	void Tile::setCanHaveHouse(bool value) {
		if(canHaveHouse == value)
			return; // Pas de changement
		if(value)
			LogicManager::getInstance().addPossibleHouseLocation(this);
		else
			LogicManager::getInstance().removePossibleHouseLocation(this);
		canHaveHouse = value;
	}

	bool Tile::getCanHaveHouse() const {
		return canHaveHouse;
	}

	bool Tile::updateCanHaveHouse() {
		int checkMinX = this->getX() - (House::minSizeX + Location::getMaxSizeX()) / 2;
		int checkMaxX = this->getX() + (House::minSizeX + Location::getMaxSizeX()) / 2;
		int checkMinY = this->getY() - (House::minSizeY + Location::getMaxSizeY()) / 2;
		int checkMaxY = this->getY() + (House::minSizeY + Location::getMaxSizeY()) / 2;

		// On ajuste les bornes pour qu'elles restent dans les limites de la ville
		if (checkMinX < 0)
			checkMinX = 0;
		if (checkMaxX >= LogicManager::getInstance().getTown()->getSizeX())
			checkMaxX = LogicManager::getInstance().getTown()->getSizeX() - 1;
		if (checkMinY < 0)
			checkMinY = 0;
		if (checkMaxY >= LogicManager::getInstance().getTown()->getSizeY())
			checkMaxY = LogicManager::getInstance().getTown()->getSizeY() - 1;

		// On regarde s'il y a une collision avec une autre Location dans la zone d�finie
		for (int checkX = checkMinX; checkX <= checkMaxX; checkX++) {
			for (int checkY = checkMinY; checkY <= checkMaxY; checkY++) {
				Models::Location* otherLocation = LogicManager::getInstance().getLocationAt(checkX, checkY);
				if (otherLocation && otherLocation != this && this->collisionWith(*otherLocation)) {
					// Collision avec une autre structure d�tect�e
					setCanHaveHouse(false);
					break;
				}
			}
			// "Break 2" n'existe pas en C++, et je ne vais pas utiliser un Goto (on n'est plus sur une TI au lyc�e...)
			if (!getCanHaveHouse())
				break;
		}
		return getCanHaveHouse();
	}

	void Tile::updateAttractiveness() {
		float attractivenessBefore = getAttractiveness(Pop::Gueux);

		// On appelle la m�thode parente pour mettre � jour l'attractivit� en fonction des services disponibles
		ServiceReceiver::updateAttractiveness();

		if (attractivenessBefore > 0.0f && getAttractiveness(Pop::Gueux) <= 0.0f) {
			// On retire ce tile de la liste des emplacements possibles pour une maison
			LogicManager::getInstance().removePossibleHouseLocation(this);
		} 
		else if (attractivenessBefore <= 0.0f && getAttractiveness(Pop::Gueux) > 0.0f) {
			// On ajoute ce tile � la liste des emplacements possibles pour une maison
			LogicManager::getInstance().addPossibleHouseLocation(this);
		}
	}
}