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
	};
}

