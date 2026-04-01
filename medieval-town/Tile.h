#pragma once
#include "Location.h"
#include <vector>
#include <map>
#include "Service.h"
#include "ServiceReceiver.h" 
#include <cstdint>
using int32 = int32_t; // Match le type "int" d'Unreal Engine
using std::vector;

namespace Models {

	// Forward declarations
	class Building;

	// Case (tuile) dans la grille de la ville, utilisée pour calculer l'attractivité des emplacements de futures maisons
	class Tile : public Location, public ServiceReceiver
	{
	public:
		Tile(int32 x, int32 y);


		bool getCanHaveHouse() const;
		// Vérifie et met à jour si ce tile peut recevoir une maison en fonction des constructions autour, et renvoie le résultat
		bool updateCanHaveHouse(); 

		// Ajoute une Location à la liste des causes empêchant ce tile de recevoir une maison, et canHaveHouse à true
		void addNoHouseCause(Location* location); 
		// Retire une Location de la liste des causes empêchant ce tile de recevoir une maison, et met à jour canHaveHouse si la liste est vide
		void removeNoHouseCause(Location* location);

	protected:
		// Ce tile peut-il recevoir une maison en fonction des constructions autour ? 
		bool canHaveHouse;

		// Liste des Locations à proximité qui empêchent ce tile de recevoir une maison (espace minimum non disponible). Cette liste est mise à jour à chaque création ou destruction de Construction ou de Building par le LogicManager
		vector<Location*> noHouseCauses;

		// Indique si ce tile peut recevoir une maison en fonction des constructions autour (on vérifie l'attractivité pour savoir s'il doit être dans la liste des emplacements possibles pour une maison). Appelé par removeNoHouseCause.
		void setCanHaveHouse();

		// Spécifie que ce tile n'est pas éligible pour recevoir une maison. Appelé par addNoHouseCause.
		void setCannotHaveHouse();

		// Surcharge de updateAttractiveness() de ServiceReceiver pour mettre à jour canHaveHouse en fonction de l'attractivité
		void updateAttractiveness() override;
	};
}

