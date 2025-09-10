#pragma once
#include "Construction.h"

namespace Models
{
	// Chantier de construction d'un b�timent de service
	class ConstructionBuilding : public Construction
	{
	public:
		ConstructionBuilding(const BuildingType& type, Family* family, int x, int y, int rotation);
		const BuildingType& getType() const;
		Family* getFamily() const;

		// Surcharges de la classe parent

		void logicTick() override;

	protected:
		const BuildingType& type; // Type de b�timent en cours de construction. Un building ne change jamais de type, donc on le stocke par r�f�rence et en const
		Family* family; // Famille propri�taire du b�timent ; nullptr si pas de propri�taire, donc on le stocke par pointeur
	};
}

