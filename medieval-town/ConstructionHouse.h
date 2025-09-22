#pragma once
#include "Construction.h"


namespace Models
{
	// Chantier de construction d'une maison d'habitation
    class ConstructionHouse : public Construction
    {
    public:
        ConstructionHouse(int x, int y, int rotation, int sizeX, int sizeY, int niveau);

		// Getters
		int getNiveau() const;

        // Surcharges de la classe parent
		void logicTick() override;

	protected: 
		int niveau; // Niveau de la maison qui sera construite
    };
}

