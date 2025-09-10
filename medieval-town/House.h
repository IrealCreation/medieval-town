#pragma once
#include "Location.h"

namespace Models
{
    class House : public Location
    {
    public:
        House(int x, int y, int rotation, int sizeX, int sizeY);

        // Getters
        int getSizeX() const;
        int getSizeY() const;

		void logicTick();

    protected:
        int sizeX; // Taille de la maison en X
		int sizeY; // Taille de la maison en Y
		int dateCreation; // Date de création de la maison (fin du chantier de construction)

        // TODO: Pops résidentes
    };
}

