#pragma once
#include "Construction.h"
#include <map>
#include <cstdint>
using int32 = uint32_t; // Match le type "int" d'Unreal Engine


namespace Models
{
	// Forward declarations
	enum class Pop;

	// Chantier de construction d'une maison d'habitation
    class ConstructionHouse : public Construction
    {
    public:
        ConstructionHouse(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau, std::map<Pop, int32> previewPops);

		// Getters
		int32 getNiveau() const;
		std::map<Pop, int32> getPreviewPops() const;

        // Surcharges de la classe parent
		void logicTick() override;

	protected: 
		int32 niveau; // Niveau de la maison qui sera construite
		std::map<Pop, int32> previewPops; // Populations prévues dans la maison une fois construite
    };
}

