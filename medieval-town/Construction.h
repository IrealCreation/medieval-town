#pragma once
#include "Location.h" // Classe parent : on doit inclure son header
#include <cstdint>
using int32 = int32_t; // Match le type "int" d'Unreal Engine

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

		int32 getDaysDone() const; // Jours de construction effectués
		int32 getDaysRemaining() const; // Jours restants avant la fin de la construction
		int32 percentDone() const; // Pourcentage de la construction effectuée

	protected:
		Construction(int32 x, int32 y, int32 rotation, float sizeX, float sizeY);
		int32 dateStart; // Date de début du chantier de construction
		int32 constructionTime; // Durée nécessaire à la construction, en jours
		int32 daysDone; // Jours de construction effectués
	};

}

