#pragma once
#include "Location.h"
#include <map>
#include "Pop.h"
#include "Service.h"
#include "ServiceReceiver.h" 

namespace Models
{
    // Forward declarations
	class Building;

    class House : public Location, public ServiceReceiver
    {
    public:
        House(int x, int y, int rotation, int sizeX, int sizeY, int niveau);

        // Getters
        int getNiveau() const;
        int getPop(Pop pop) const; // Retourne le nombre de pops résidentes dans la maison pour le type de pop donné
		int getPopTotal() const; // Retourne le nombre total de pops résidentes dans la maison

		void logicTick();

    protected:
		int dateCreation; // Date de création de la maison (fin du chantier de construction)
		int niveau; // Niveau de la maison, lui permettant d'accueillir plus de pop et de meilleures pops

		std::map<Pop, int> pops; // Populations résidentes dans la maison
    };
}

