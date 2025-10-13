#pragma once
#include "Location.h"
#include <map>
#include "Service.h"
#include "ServiceReceiver.h" 

namespace Models {

	// Forward declarations
	class Building;

	// Case (tuile) dans la grille de la ville, utilis�e pour calculer l'attractivit� des emplacements de futures maisons
	class Tile : public Location, public ServiceReceiver
	{
	public:
		Tile(int x, int y);

		void setCanHaveHouse(bool value);
		bool getCanHaveHouse() const;
		// V�rifie et met � jour si ce tile peut recevoir une maison en fonction des constructions autour, et renvoie le r�sultat
		bool updateCanHaveHouse(); 

	protected:
		// Ce tile peut-il recevoir une maison ?
		bool canHaveHouse;

		// Surcharge de updateAttractiveness() de ServiceReceiver pour mettre � jour canHaveHouse en fonction de l'attractivit�
		void updateAttractiveness() override;
	};
}

