#include "Construction.h"
#include "LogicManager.h"
#include "BuildingType.h"
#include "Town.h"

namespace Models
{
	Construction::Construction(int x, int y, int rotation, float sizeX, float sizeY)
		: Location(x, y, rotation, sizeX, sizeY), daysDone(0) 
	{
		dateStart = LogicManager::getInstance().getTown()->getDate(); // On initialise la date de d�but du chantier � la date actuelle de la ville
		// constructionTime doit �tre initialis� dans les classes filles
	}
	void Construction::logicTick()
	{
		// Incr�menter le nombre de jours de construction effectu�s
		daysDone++;

		// Dans classe fille, v�rifier si la construction est termin�e
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