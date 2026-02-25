#pragma once
#include "Construction.h"
#include <cstdint>
using int32 = int32_t; // Match le type "int" d'Unreal Engine

namespace Models
{
	// Chantier de construction d'un bâtiment de service
	class ConstructionBuilding : public Construction
	{
	public:
		ConstructionBuilding(const BuildingType& type, Family* family, int32 x, int32 y, int32 rotation);
		const BuildingType& getType() const;
		Family* getFamily() const;

		// Surcharges de la classe parent

		void logicTick() override;

	protected:
		const BuildingType& type; // Type de bâtiment en cours de construction. Un building ne change jamais de type, donc on le stocke par référence et en const
		Family* family; // Famille propriétaire du bâtiment ; nullptr si pas de propriétaire, donc on le stocke par pointeur
	};
}

