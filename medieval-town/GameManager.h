#pragma once
#include "Town.h"
#include "BuildingType.h"
#include "Family.h"

class GameManager
{
public:
	GameManager();

	// Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)
	void LogicTick();

	Models::Town getTown();

	// Débute la construction d'un bâtiment
	void startConstruction(const Models::BuildingType& type, const Models::Location& location, Models::Family& family);
	// Termine la construction d'un bâtiment
	void constructionDone(Models::Construction& construction);

protected:
	Models::Town town; // La ville dans laquelle se déroule la partie
};

