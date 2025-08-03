#pragma once
#include "Town.h"
#include "BuildingType.h"
#include "Family.h"

// Le GameManager remplit deux utilisés : servir de chef d'orchestre entre toutes les classes Models ; et servir de point d'interaction entre les classes Models et le moteur de jeu
class GameManager
{
public:
	GameManager();

	// Référence au GameManager unique de la partie
	static GameManager& getInstance();

	// Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)
	void LogicTick();

	Models::Town getTown();

	// Débute la construction d'un bâtiment
	void startConstruction(const Models::BuildingType& type, const Models::Location& location, Models::Family* family);
	// Termine la construction d'un bâtiment
	void constructionDone(Models::Construction& construction);

protected:
	Models::Town town; // La ville dans laquelle se déroule la partie
	static GameManager instance; // Instance unique du GameManager
};

