#include "ConstructionHouse.h"

namespace Models
{
    ConstructionHouse::ConstructionHouse(int x, int y, int rotation, int sizeX, int sizeY)
		: Construction(x, y, rotation), sizeX(sizeX), sizeY(sizeY)
    {
		this->constructionTime = sizeX * sizeY; // Temps de construction égal à la surface de la maison
    }

    void ConstructionHouse::logicTick()
    {
        Construction::logicTick();
    }
}
