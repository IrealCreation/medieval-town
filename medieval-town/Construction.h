#pragma once
#include "Location.h"
#include "BuildingType.h"
#include "Family.h"

namespace Models
{
	// Chantier de construction d'un bâtiment
	class Construction : public Location
	{
	public:
		Construction(const BuildingType& type, const Location& location, Family* family);
		void LogicTick(); // Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)

		const BuildingType& getType() const;
		Family* getFamily() const; 

		int getDaysDone() const; // Jours de construction effectués
		int getDaysRemaining() const; // Jours restants avant la fin de la construction
		int percentDone() const; // Pourcentage de la construction effectuée

	protected:
		const BuildingType& type; // Type de bâtiment en cours de construction. Un building ne change jamais de type, donc on le stocke par référence et en const
		Family* family; // Famille propriétaire du bâtiment ; nullptr si pas de propriétaire, donc on le stocke par pointeur
		int dateStart; // Date de début du chantier de construction
		int daysDone; // Jours de construction effectués
	};

}

