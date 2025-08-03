#include "Construction.h"
#include "GameManager.h"

namespace Models
{
	Construction::Construction(const BuildingType& type, const Location& location, Family* family)
		: Location(location), type(type), family(family), dateStart(0), daysDone(0) {}
	void Construction::LogicTick()
	{
		// Incrémenter le nombre de jours de construction effectués
		daysDone++;

		if (daysDone >= type.getConstructionTime()) 
		{
			// Fin de la construction
			GameManager::getInstance().constructionDone(*this);
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