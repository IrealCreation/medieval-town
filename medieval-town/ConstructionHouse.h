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
		int getSizeX() const;
		int getSizeY() const;
		int getNiveau() const;


        // Surcharges de la classe parent

		void logicTick() override;

	protected: 
		int sizeX; // Taille de la maison en X
		int sizeY; // Taille de la maison en Y
		int niveau; // Niveau de la maison qui sera construite
    };
}

