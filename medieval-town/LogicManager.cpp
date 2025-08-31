#include "LogicManager.h"
#include "Town.h"
#include "BuildingType.h"
#include "Building.h"
#include "Family.h"
#include "Location.h"
#include "Construction.h"
#include <iostream> // Pour le log()

using std::string;
using std::make_unique;
using std::make_shared;

LogicManager::LogicManager() {}

LogicManager& LogicManager::getInstance()
{
	return LogicManager::instance;
}

void LogicManager::startGame()
{
	// Création de la ville
	this->town = make_unique<Models::Town>("Lorrez-le-Bocage");
	town->startTown();

	// Création des familles
	unique_ptr<Models::Family> family1 = make_unique<Models::Family>("Salviati");
	this->town->addFamily(std::move(family1));
	unique_ptr<Models::Family> family2 = make_unique<Models::Family>("Legrand");
	this->town->addFamily(std::move(family2));
}

void LogicManager::logicTick()
{
	this->log("--- Jour " + std::to_string(this->town->getDate()) + " ---");

	this->town->logicTick();

	// Log de l'état des familles
	for (const auto family : this->getTown()->getFamilies()) {
		this->log("Famille " + family->getName() + " : or " + std::to_string(family->getGold()) + " - prestige : " + std::to_string(family->getPrestige()));
	}
}

void LogicManager::log(string message) {
	std::cout << message << "\n";
}

Models::Town* LogicManager::getTown()
{
	return this->town.get();
}

void LogicManager::startConstruction(const Models::BuildingType* type, Models::Family* family, int x, int y, int rotation)
{
	unique_ptr<Models::Construction> construction = make_unique<Models::Construction>(*type, family, x, y, rotation);
	family->addConstruction(construction.get());
	// Enfin, on bouge le unique_ptr dans Town qui en a désormais la charge
	town->addConstruction(std::move(construction));
}
void LogicManager::constructionDone(Models::Construction* construction)
{
	// On crée le nouveau bâtiment à partir du chantier de construction
	unique_ptr <Models::Building> building = make_unique<Models::Building>(construction->getType(), construction->getFamily(), construction->getX(), construction->getY(), construction->getRotation());
	construction->getFamily()->addBuilding(building.get());
	town->addBuilding(std::move(building));
	
	// On supprime le chantier de construction
	construction->getFamily()->removeConstruction(construction);
	town->removeConstruction(construction);

	// UE : despawn l'objet Construction, spawn l'objet Building, petite animation de construction achevée
}

