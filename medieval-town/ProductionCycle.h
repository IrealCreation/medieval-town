#pragma once
#include <cstdint>
#include <map>
#include "Resource.h"
using int32 = int32_t; // Match le type "int" d'Unreal Engine


namespace Models {
	// Cycle de production de ressources des bâtiments
	class ProductionCycle
	{
		public:
			ProductionCycle(int32 queue,
				const std::map<Resource, int32>& resourceInputs,
				const std::map<Resource, int32>& resourceOutputs);
			int32 getQueue() const;
			const std::map<Resource, int32>& getResourceInputs() const;
			const std::map<Resource, int32>& getResourceOutputs() const;

		protected:
			int32 queue; // Ordre d'exécution lors du tick de production (0 à 2 : 0 étant les ressources primaires ne nécessitant aucune autre ressource pour être produites, puis chaque queue successive utilisant les ressources produites dans la queue inférieure)
			std::map<Resource, int32> resourceInputs; // Ressources consommées par le cycle de production
			std::map<Resource, int32> resourceOutputs; // Ressources produites par le cycle de production

	};
}

