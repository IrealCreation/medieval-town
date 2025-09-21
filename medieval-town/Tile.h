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
	};
}

