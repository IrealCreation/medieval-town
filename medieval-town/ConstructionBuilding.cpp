#include "ConstructionBuilding.h"
#include "LogicManager.h"
#include "BuildingType.h"
#include "Town.h"

namespace Models
{
	ConstructionBuilding::ConstructionBuilding(const BuildingType& type, Family* family, int32 x, int32 y, int32 rotation)
		: Construction(x, y, rotation, type.getSizeX(), type.getSizeY()), type(type), family(family) 
	{
		constructionTime = type.getConstructionTime(); // On initialise le temps de construction à partir du type de bâtiment

		// Génération de l'ID
		setId();
	}

	void ConstructionBuilding::logicTick() 
	{
		// Appel de la logique de la classe parent
		Construction::logicTick();

		if (daysDone >= constructionTime)
		{
			// Fin de la construction
			LogicManager::getInstance().constructionBuildingDone(this);
		}
	}
	void ConstructionBuilding::setId()
	{
		// ID généré à partir du type et de la date de début de construction
		id = "Construction" + type.getName() + "_" + std::to_string(getX()) + "_" + std::to_string(getY()) + "_" + std::to_string(dateStart);
		// Appel de la fonction parente pour ajouter cette Location à la map du LogicManager
		Location::setId();
	}
	const BuildingType& ConstructionBuilding::getType() const
	{
		return type;
	}
	Family* ConstructionBuilding::getFamily() const
	{
		return family;
	}
}