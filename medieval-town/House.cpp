#include "House.h"
#include "LogicManager.h"
#include "Town.h"

namespace Models
{
	House::House(int x, int y, int rotation, int sizeX, int sizeY)
		: Location(x, y, rotation), sizeX(sizeX), sizeY(sizeY)
	{
		dateCreation = LogicManager::getInstance().getTown()->getDate(); // On initialise la date de cr�ation � la date actuelle de la ville
	}
	int House::getSizeX() const
	{
		return sizeX;
	}
	int House::getSizeY() const
	{
		return sizeY;
	}
	void House::logicTick()
	{
		// TODO: g�rer les pops r�sidentes, leurs besoins, leur croissance...
	}
}
