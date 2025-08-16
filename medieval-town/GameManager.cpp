#include "GameManager.h"

GameManager::GameManager()
{
	GameManager::instance = *this;
}

GameManager& GameManager::getInstance()
{
	return GameManager::instance;
}

void GameManager::startGame()
{
	// Création de la ville
	this->town = Models::Town("Villebéon");
	town.startTown();

	// Création des familles
	Models::Family family1("Salviati");
	this->town.addFamily(family1);
	Models::Family family2("Legrand");
	this->town.addFamily(family2);
}

void GameManager::logicTick()
{
	town.logicTick();
}
Models::Town GameManager::getTown()
{
	return town;
}
void GameManager::startConstruction(const Models::BuildingType& type, const Models::Location& location, Models::Family* family)
{
	Models::Construction construction(type, location, family);
	town.addConstruction(construction);
	family->addConstruction(&construction);
}
void GameManager::constructionDone(Models::Construction* construction)
{
	// On crée le nouveau bâtiment à partir du chantier de construction
    Models::Building building(construction->getType(), construction->getFamily(), construction->getX(), construction->getY());
	town.addBuilding(building);
	construction->getFamily()->addBuilding(&building);
	
	// On supprime le chantier de construction
	town.removeConstruction(construction);
	construction->getFamily()->removeConstruction(construction);

	// UE : despawn l'objet Construction, spawn l'objet Building, petite animation de construction achevée
}

