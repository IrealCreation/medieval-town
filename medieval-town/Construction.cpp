#include "Construction.h"
#include "LogicManager.h"
#include "BuildingType.h"

namespace Models
{
	Construction::Construction(const BuildingType& type, Family* family, int x, int y, int rotation)
		: Location(x, y, rotation), type(type), family(family), dateStart(0), daysDone(0) {}
	void Construction::logicTick()
	{
		// Incrémenter le nombre de jours de construction effectués
		daysDone++;

		if (daysDone >= type.getConstructionTime()) 
		{
			// Fin de la construction
			LogicManager::getInstance().constructionDone(this);
		}
	}
	const BuildingType& Construction::getType() const
	{
		return type;
	}
	Family* Construction::getFamily() const
	{
		return family;
	}
	int Construction::getDaysDone() const
	{
		return daysDone;
	}
	int Construction::getDaysRemaining() const
	{
		return type.getConstructionTime() - daysDone;
	}
	int Construction::percentDone() const
	{
		return (daysDone * 100) / type.getConstructionTime();
	}
}