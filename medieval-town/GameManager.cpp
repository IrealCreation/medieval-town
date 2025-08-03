#include "GameManager.h"

void GameManager::LogicTick()
{
	town.LogicTick();
}
Models::Town GameManager::getTown()
{
	return town;
}
void GameManager::startConstruction(const Models::BuildingType& type, const Models::Location& location, Models::Family& family)
{
	Models::Construction construction(type, location, family);
	town.addConstruction(construction);
	family.addConstruction(construction);
}
void GameManager::constructionDone(Models::Construction& construction)
{
	// On crée le nouveau bâtiment à partir du chantier de construction
    Models::Building building(construction.getType(), construction, &construction.getFamily());

	town.addBuilding(building);
	construction.getFamily().addBuilding(building);
	
	// On supprime le chantier de construction
	town.removeConstruction(construction);
	construction.getFamily().removeConstruction(construction);
}

