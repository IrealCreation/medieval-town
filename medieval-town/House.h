#pragma once
#include "Location.h"
#include <map>
#include "Pop.h"
#include "Service.h"
#include "ServiceReceiver.h" 
#include <cstdint>
using int32 = uint32_t; // Match le type "int" d'Unreal Engine

namespace Models
{
    // Forward declarations
	class Building;

    class House : public Location, public ServiceReceiver
    {
    public:
        House(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau);

        // Getters
        int32 getNiveau() const;
        int32 getPop(Pop pop) const; // Retourne le nombre de pops résidentes dans la maison pour le type de pop donné
		int32 getPopTotal() const; // Retourne le nombre total de pops résidentes dans la maison

		void logicTick();

        static const int32 minSizeX = 4; // Taille minimale sur l'axe X d'une maison
        static const int32 minSizeY = 6; // Taille minimale sur l'axe Y d'une maison

    protected:
		int32 dateCreation; // Date de création de la maison (fin du chantier de construction)
		int32 niveau; // Niveau de la maison, lui permettant d'accueillir plus de pop et de meilleures pops

		std::map<Pop, int32> pops; // Populations résidentes dans la maison
    };
}

