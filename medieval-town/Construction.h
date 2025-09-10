#pragma once
#include "Location.h" // Classe parent : on doit inclure son header

namespace Models
{
	// Forward declarations pour �viter les d�pendances circulaires
	class Family; 
	class BuildingType;

	// Chantier de construction. Classe parent de ConstructionBuilding (pour un b�timent de service) et ConstructionHouse (pour une maison d'habitation)
	class Construction : public Location
	{
	public:
		virtual void logicTick(); // Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)

		int getDaysDone() const; // Jours de construction effectu�s
		int getDaysRemaining() const; // Jours restants avant la fin de la construction
		int percentDone() const; // Pourcentage de la construction effectu�e

	protected:
		Construction(int x, int y, int rotation);
		int dateStart; // Date de d�but du chantier de construction
		int constructionTime; // Dur�e n�cessaire � la construction, en jours
		int daysDone; // Jours de construction effectu�s
	};

}

