#include "ConstructionHouse.h"
#include "LogicManager.h"

namespace Models
{
    ConstructionHouse::ConstructionHouse(int x, int y, int rotation, int sizeX, int sizeY, int niveau)
		: Construction(x, y, rotation, sizeX, sizeY), niveau(niveau)
    {
		this->constructionTime = sizeX * sizeY; // Temps de construction égal à la surface de la maison
    }

    int ConstructionHouse::getNiveau() const
    {
        return niveau;
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
