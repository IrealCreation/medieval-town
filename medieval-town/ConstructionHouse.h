#pragma once
#include "Construction.h"


namespace Models
{
	// Chantier de construction d'une maison d'habitation
    class ConstructionHouse : public Construction
    {
    public:
        ConstructionHouse(int x, int y, int rotation, int sizeX, int sizeY);

		// Getters
		int getSizeX() const;
		int getSizeY() const;


        // Surcharges de la classe parent

		void logicTick() override;

	protected: 
		int sizeX; // Taille de la maison en X
		int sizeY; // Taille de la maison en Y
    };
}

