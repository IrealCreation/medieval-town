#pragma once
#include "Location.h"
#include <map>
#include "Pop.h"
#include "ServiceType.h"

namespace Models
{
    // Forward declarations
	class Building;

    class House : public Location
    {
    public:
        House(int x, int y, int rotation, int sizeX, int sizeY, int niveau);

        // Getters
        int getSizeX() const;
        int getSizeY() const;
        int getNiveau() const;
        int getPop(Pop pop) const; // Retourne le nombre de pops r�sidentes dans la maison pour le type de pop donn�
		int getPopTotal() const; // Retourne le nombre total de pops r�sidentes dans la maison
		Building* getServiceBuilding(Service service) const; // Retourne le b�timent de service desservant cette maison pour le service donn� ; nullptr si pas de b�timent

		void addService(Service service, Building* building); // Ajoute un b�timent de service desservant cette maison

		void logicTick();

    protected:
        int sizeX; // Taille de la maison en X
		int sizeY; // Taille de la maison en Y
		int dateCreation; // Date de cr�ation de la maison (fin du chantier de construction)
		int niveau; // Niveau de la maison, lui permettant d'accueillir plus de pop et de meilleures pops

		std::map<Pop, int> pops; // Populations r�sidentes dans la maison

		std::map<Service, Building*> serviceBuildings; // B�timents de service desservant cette maison
    };
}

