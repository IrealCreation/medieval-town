#pragma once
#include "Town.h"
#include "BuildingType.h"
#include "Family.h"

class GameManager
{
public:
	GameManager();

	// Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)
	void LogicTick();

	Models::Town getTown();

	// D�bute la construction d'un b�timent
	void startConstruction(const Models::BuildingType& type, const Models::Location& location, Models::Family& family);
	// Termine la construction d'un b�timent
	void constructionDone(Models::Construction& construction);

protected:
	Models::Town town; // La ville dans laquelle se d�roule la partie
};

