#include "Tile.h"
#include "House.h"
#include "LogicManager.h"
#include "Town.h"

namespace Models
{
	Tile::Tile(int32 x, int32 y) : Location(x, y, 0) 
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

	void Tile::setCannotHaveHouse() {
		if(canHaveHouse == false)
			return; // Pas de changement
		LogicManager::getInstance().removePossibleHouseLocation(this);
		canHaveHouse = false;
	}
	void Tile::setCanHaveHouse() {
		if(canHaveHouse == true)
			return; // Pas de changement
		canHaveHouse = true;
		// On ajoute ce tile à la liste des emplacements possibles pour une maison si son attractivité est > 0
		if (getAttractiveness(Pop::Gueux) > 0) {
			LogicManager::getInstance().addPossibleHouseLocation(this);
		}
	}

	bool Tile::getCanHaveHouse() const {
		return canHaveHouse;
	}

	bool Tile::updateCanHaveHouse() {
		int32 checkMinX = this->getX() - (House::minSizeX + Location::getMaxSizeX()) / 2;
		int32 checkMaxX = this->getX() + (House::minSizeX + Location::getMaxSizeX()) / 2;
		int32 checkMinY = this->getY() - (House::minSizeY + Location::getMaxSizeY()) / 2;
		int32 checkMaxY = this->getY() + (House::minSizeY + Location::getMaxSizeY()) / 2;

		// On ajuste les bornes pour qu'elles restent dans les limites de la ville
		if (checkMinX < 0)
			checkMinX = 0;
		if (checkMaxX >= LogicManager::getInstance().getTown()->getSizeX())
			checkMaxX = LogicManager::getInstance().getTown()->getSizeX() - 1;
		if (checkMinY < 0)
			checkMinY = 0;
		if (checkMaxY >= LogicManager::getInstance().getTown()->getSizeY())
			checkMaxY = LogicManager::getInstance().getTown()->getSizeY() - 1;

		// On regarde s'il y a une collision avec une autre Location dans la zone définie
		for (int32 checkX = checkMinX; checkX <= checkMaxX; checkX++) {
			for (int32 checkY = checkMinY; checkY <= checkMaxY; checkY++) {
				Models::Location* otherLocation = LogicManager::getInstance().getLocationAt(checkX, checkY);
				if (otherLocation && otherLocation != this && this->collisionWith(*otherLocation)) {
					// Collision avec une autre structure détectée : on ne peut pas avoir de maison, fin de la vérification
					setCannotHaveHouse();
					return getCanHaveHouse();
				}
			}
		}
		return getCanHaveHouse();
	}

	void Tile::updateAttractiveness() {
		if(this->getX() == 20 && this->getY() == 20)
		{
			// Point d'arrêt de debug
		}
		int32 attractivenessBefore = getAttractiveness(Pop::Gueux);

		// On appelle la méthode parente pour mettre à jour l'attractivité en fonction des services disponibles
		ServiceReceiver::updateAttractiveness();

		int32 attractivenessAfter = getAttractiveness(Pop::Gueux);

		// Si l'attractivité est passée de plus de 0 à 0...
		if (attractivenessBefore > 0 && attractivenessAfter <= 0) {
			// ... on retire ce tile de la liste des emplacements possibles pour une maison
			LogicManager::getInstance().removePossibleHouseLocation(this);
		}
		// Si l'attractivité est passée de 0 à plus de 0, et que le tile peut recevoir une maison...
		else if (attractivenessBefore <= 0 && attractivenessAfter > 0 && getCanHaveHouse()) {
			// ... on ajoute ce tile à la liste des emplacements possibles pour une maison
			LogicManager::getInstance().addPossibleHouseLocation(this);
		}
	}
}