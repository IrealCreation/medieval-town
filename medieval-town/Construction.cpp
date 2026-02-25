#include "Construction.h"
#include "LogicManager.h"
#include "BuildingType.h"
#include "Town.h"

namespace Models
{
	Construction::Construction(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY)
		: Location(x, y, rotation, sizeX, sizeY)
	{
		dateStart = LogicManager::getInstance().getTown()->getDate(); // On initialise la date de début du chantier à la date actuelle de la ville
		// constructionTime doit être initialisé dans les classes filles
	}
	void Construction::logicTick()
	{
		// Incrémenter le nombre de jours de construction effectués
		daysDone++;

		// Dans classe fille, vérifier si la construction est terminée
	}
	int32 Construction::getDaysDone() const
	{
		return daysDone;
	}
	int32 Construction::getDaysRemaining() const
	{
		return constructionTime - daysDone;
	}
	int32 Construction::percentDone() const
	{
		return (daysDone * 100) / constructionTime;
	}
}