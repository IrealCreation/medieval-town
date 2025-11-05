#include "ConstructionHouse.h"
#include "LogicManager.h"

namespace Models
{
    ConstructionHouse::ConstructionHouse(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau, std::map<Pop, int32> previewPops)
		: Construction(x, y, rotation, sizeX, sizeY), niveau(niveau), previewPops(previewPops)
    {
		this->constructionTime = sizeX * sizeY / 8; // Temps de construction égal à la surface de la maison divisé par 8
    }

    int32 ConstructionHouse::getNiveau() const
    {
        return niveau;
    }
    std::map<Pop, int32> ConstructionHouse::getPreviewPops() const
    {
        return previewPops;
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
