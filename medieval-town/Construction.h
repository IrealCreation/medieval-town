#pragma once
#include "Location.h"

namespace Models
{
	// Forward declarations pour �viter les d�pendances circulaires
	class Family; 
	class BuildingType;

	// Chantier de construction d'un b�timent
	class Construction : public Location
	{
	public:
		Construction(const BuildingType& type, const Location& location, Family* family);
		void logicTick(); // Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)

		const BuildingType& getType() const;
		Family* getFamily() const; 

		int getDaysDone() const; // Jours de construction effectu�s
		int getDaysRemaining() const; // Jours restants avant la fin de la construction
		int percentDone() const; // Pourcentage de la construction effectu�e

	protected:
		const BuildingType& type; // Type de b�timent en cours de construction. Un building ne change jamais de type, donc on le stocke par r�f�rence et en const
		Family* family; // Famille propri�taire du b�timent ; nullptr si pas de propri�taire, donc on le stocke par pointeur
		int dateStart; // Date de d�but du chantier de construction
		int daysDone; // Jours de construction effectu�s
	};

}

