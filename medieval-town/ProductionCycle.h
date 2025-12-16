#pragma once
#include <cstdint>
#include <vector>
#include "Resource.h"
using int32 = int32_t; // Match le type "int" d'Unreal Engine


namespace Models {
	// Cycle de production de ressources des bâtiments
	class ProductionCycle
	{
		public:
			ProductionCycle(int32 productionByTick,
				const std::vector<Resource>& resourceInputs,
				const std::vector<Resource>& resourceOutputs);
			int32 getProductionByTick() const;
			const std::vector<Resource>& getResourceInputs() const;
			const std::vector<Resource>& getResourceOutputs() const;

		protected:
			int32 productionByTick; // Quantité produite par tick de production
			std::vector<Resource> resourceInputs; // Ressources consommées par le cycle de production
			std::vector<Resource> resourceOutputs; // Ressources produites par le cycle de production

	};
}

