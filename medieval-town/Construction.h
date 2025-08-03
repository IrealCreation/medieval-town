#pragma once
#include "Location.h"
#include "BuildingType.h"
#include "Family.h"

namespace Models
{
	// Chantier de construction d'un b�timent
	class Construction : public Location
	{
	public:
		Construction(const BuildingType& type, const Location& location, Family& family);
		void LogicTick(); // Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)

		BuildingType getType() const; // Type de b�timent en cours de construction
		Family getFamily() const; // Famille propri�taire du b�timent (peut �tre nullptr si pas de propri�taire)

		int getDaysDone() const; // Jours de construction effectu�s
		int getDaysRemaining() const; // Jours restants avant la fin de la construction
		int percentDone() const; // Pourcentage de la construction effectu�e

	protected:
		BuildingType type; // Type de b�timent en cours de construction
		Family family; // Famille propri�taire du b�timent (peut �tre nullptr si pas de propri�taire)
		int dateStart; // Date de d�but du chantier de construction
		int daysDone; // Jours de construction effectu�s
	};

}

