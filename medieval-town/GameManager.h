#pragma once
#include "Town.h"
#include "BuildingType.h"
#include "Building.h"
#include "Family.h"
#include "Location.h"
#include "Construction.h"

//// Forward declarations pour �viter les d�pendances circulaires
//namespace Models {
//	class Town;
//	class BuildingType;
//	class Family;
//}

// Le GameManager remplit deux utilis�s : servir de chef d'orchestre entre toutes les classes Models ; et servir de point d'interaction entre les classes Models et le moteur de jeu
class GameManager
{

public:
	GameManager();

	// R�f�rence au GameManager unique de la partie
	static GameManager& getInstance();

	// D�but de la partie
	void startGame();

	// Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)
	void logicTick();

	Models::Town getTown();

	// D�bute la construction d'un b�timent
	void startConstruction(const Models::BuildingType& type, const Models::Location& location, Models::Family* family);
	// Termine la construction d'un b�timent
	void constructionDone(Models::Construction* construction);

protected:
	Models::Town town; // La ville dans laquelle se d�roule la partie
	static GameManager instance; // Instance unique du GameManager
};

