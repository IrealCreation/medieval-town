#include "Construction.h"
#include "LogicManager.h"
#include "BuildingType.h"
#include "Town.h"

namespace Models
{
	Construction::Construction(int x, int y, int rotation, float sizeX, float sizeY)
		: Location(x, y, rotation, sizeX, sizeY), daysDone(0) 
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
	int Construction::getDaysDone() const
	{
		return daysDone;
	}
	int Construction::getDaysRemaining() const
	{
		return constructionTime - daysDone;
	}
	int Construction::percentDone() const
	{
		return (daysDone * 100) / constructionTime;
	}
}