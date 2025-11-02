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

		// Spécifie que ce tile n'est pas éligible pour recevoir une maison. Pour spécifier qu'il a la possibilité de redevenir éligible, il faut appeler updateCanHaveHouse()
		void setCannotHaveHouse();

		bool getCanHaveHouse() const;
		// Vérifie et met à jour si ce tile peut recevoir une maison en fonction des constructions autour, et renvoie le résultat
		bool updateCanHaveHouse(); 

	protected:
		// Ce tile peut-il recevoir une maison en fonction des constructions autour ?
		bool canHaveHouse;

		// Indique si ce tile peut recevoir une maison en fonction des constructions autour (on vérifie l'attractivité pour savoir s'il doit être dans la liste des emplacements possibles pour une maison). Protected car il ne doit être appelé que depuis updateCanHaveHouse() qui vérifie les collisions
		void setCanHaveHouse();

		// Surcharge de updateAttractiveness() de ServiceReceiver pour mettre à jour canHaveHouse en fonction de l'attractivité
		void updateAttractiveness() override;
	};
}

