#pragma once
#include "Location.h" // Classe parent : on doit inclure son header

namespace Models
{
	// Forward declarations pour éviter les dépendances circulaires
	class Family; 
	class BuildingType;

	// Chantier de construction. Classe parent de ConstructionBuilding (pour un bâtiment de service) et ConstructionHouse (pour une maison d'habitation)
	class Construction : public Location
	{
	public:
		virtual void logicTick(); // Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)

		int getDaysDone() const; // Jours de construction effectués
		int getDaysRemaining() const; // Jours restants avant la fin de la construction
		int percentDone() const; // Pourcentage de la construction effectuée

	protected:
		Construction(int x, int y, int rotation);
		int dateStart; // Date de début du chantier de construction
		int constructionTime; // Durée nécessaire à la construction, en jours
		int daysDone; // Jours de construction effectués
	};

}

