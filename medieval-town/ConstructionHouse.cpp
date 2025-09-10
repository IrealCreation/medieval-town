#include "ConstructionHouse.h"
#include "LogicManager.h"

namespace Models
{
    ConstructionHouse::ConstructionHouse(int x, int y, int rotation, int sizeX, int sizeY)
		: Construction(x, y, rotation), sizeX(sizeX), sizeY(sizeY)
    {
		this->constructionTime = sizeX * sizeY; // Temps de construction égal à la surface de la maison
    }

    int ConstructionHouse::getSizeX() const
    {
        return sizeX;
    }

    int ConstructionHouse::getSizeY() const
    {
        return sizeY;
    }

    void ConstructionHouse::logicTick()
    {
        Construction::logicTick();
        if (daysDone >= constructionTime)
        {
            // Fin de la construction
            LogicManager::getInstance().constructionHouseDone(this);
		}
    }
}
