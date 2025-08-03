#pragma once
#include "Town.h"
#include "BuildingType.h"
#include "Family.h"

class GameManager
{
public:
	GameManager();
	void startGame();

	Models::Town getTown();

	void newBuilding(const Models::BuildingType& type, const Models::Location& location, const Models::Family& family);

protected:
	Models::Town town; // La ville dans laquelle se déroule la partie
};

