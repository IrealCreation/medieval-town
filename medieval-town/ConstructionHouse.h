#pragma once
#include "Construction.h"
#include <cstdint>
using int32 = uint32_t; // Match le type "int" d'Unreal Engine


namespace Models
{
	// Chantier de construction d'une maison d'habitation
    class ConstructionHouse : public Construction
    {
    public:
        ConstructionHouse(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau);

		// Getters
		int32 getNiveau() const;

        // Surcharges de la classe parent
		void logicTick() override;

	protected: 
		int32 niveau; // Niveau de la maison qui sera construite
    };
}

