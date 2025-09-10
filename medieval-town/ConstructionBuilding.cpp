#include "ConstructionBuilding.h"
#include "LogicManager.h"
#include "BuildingType.h"
#include "Town.h"

namespace Models
{
	ConstructionBuilding::ConstructionBuilding(const BuildingType& type, Family* family, int x, int y, int rotation)
		: Construction(x, y, rotation), type(type), family(family) 
	{
		constructionTime = type.getConstructionTime(); // On initialise le temps de construction � partir du type de b�timent
	}

	void ConstructionBuilding::logicTick() 
	{
		// Appel de la logique de la classe parent
		Construction::logicTick();

		if (daysDone >= constructionTime)
		{
			// Fin de la construction
			LogicManager::getInstance().constructionBuildingDone(this);
		}
	}
	const BuildingType& ConstructionBuilding::getType() const
	{
		return type;
	}
	Family* ConstructionBuilding::getFamily() const
	{
		return family;
	}
}