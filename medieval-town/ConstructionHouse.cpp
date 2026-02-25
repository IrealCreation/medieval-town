#include "ConstructionHouse.h"
#include "LogicManager.h"

namespace Models
{
    ConstructionHouse::ConstructionHouse(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 level, std::map<Pop, int32> previewPops)
		: Construction(x, y, rotation, sizeX, sizeY), level(level), previewPops(previewPops)
    {
		this->constructionTime = sizeX * (sizeY - 1) / 8; // Temps de construction égal à la surface de la maison divisé par 8 (-1 sur Y pour la façade avec la porte)

		// Génération de l'ID
        setId("ConstructionHouse", dateStart);
    }

    int32 ConstructionHouse::getLevel() const
    {
        return level;
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
