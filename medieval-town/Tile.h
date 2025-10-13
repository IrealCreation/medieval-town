#pragma once
#include "Location.h"
#include <map>
#include "Service.h"
#include "ServiceReceiver.h" 

namespace Models {

	// Forward declarations
	class Building;

	// Case (tuile) dans la grille de la ville, utilisée pour calculer l'attractivité des emplacements de futures maisons
	class Tile : public Location, public ServiceReceiver
	{
	public:
		Tile(int x, int y);

		void setCanHaveHouse(bool value);
		bool getCanHaveHouse() const;
		// Vérifie et met à jour si ce tile peut recevoir une maison en fonction des constructions autour, et renvoie le résultat
		bool updateCanHaveHouse(); 

	protected:
		// Ce tile peut-il recevoir une maison ?
		bool canHaveHouse;

		// Surcharge de updateAttractiveness() de ServiceReceiver pour mettre à jour canHaveHouse en fonction de l'attractivité
		void updateAttractiveness() override;
	};
}

