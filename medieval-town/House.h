#pragma once
#include "Location.h"
#include <map>
#include "Pop.h"

namespace Models
{
    class House : public Location
    {
    public:
        House(int x, int y, int rotation, int sizeX, int sizeY, int niveau);

        // Getters
        int getSizeX() const;
        int getSizeY() const;
        int getNiveau() const;

		void logicTick();

    protected:
        int sizeX; // Taille de la maison en X
		int sizeY; // Taille de la maison en Y
		int dateCreation; // Date de création de la maison (fin du chantier de construction)
		int niveau; // Niveau de la maison, lui permettant d'accueillir plus de pop et de meilleures pops

		std::map<Pop, int> pops; // Populations résidentes dans la maison
    };
}

