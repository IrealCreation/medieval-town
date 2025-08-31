#pragma once
#include <string>
#include <memory>
#include <map>
using std::unique_ptr;
using std::shared_ptr;
using std::string;
using std::map;

// Forward declarations pour éviter les dépendances circulaires
namespace Models {
	class Town;
	class BuildingType;
	class Building;
	class Family;
	class Location;
	class Construction;
}

// Permet de créer des tableaux à trois dimensions : X, Y, Building
//typedef std::map<int, Models::Building*> MapBuildingLocation;
//typedef std::map<int, MapBuildingLocation> MapBuildingLocationXY;

// Le GameManager remplit deux utilisés : servir de chef d'orchestre entre toutes les classes Models ; et servir de point d'interaction entre les classes Models et le moteur de jeu
class LogicManager
{

public:
	// On supprime l'opérateur de copie pour ne pas que notre instance soit dupliquée
	LogicManager(const LogicManager&) = delete;

	// Référence au GameManager unique de la partie
	static LogicManager& getInstance();

	// Début de la partie
	void startGame();

	// Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)
	void logicTick();

	// Log de debug
	void log(string message);

	// Retourne un raw pointer vers la ville ; le cycle de vie de la ville reste géré par le LogicManager
	Models::Town* getTown();

	// Débute la construction d'un bâtiment
	void startConstruction(const Models::BuildingType& type, Models::Family* family, int x, int y, int rotation);
	// Termine la construction d'un bâtiment
	void constructionDone(Models::Construction* construction);
	// Ajoute directement un bâtiment
	void createBuilding(const Models::BuildingType& type, Models::Family* family, int x, int y, int rotation);

protected:
	LogicManager();

	unique_ptr<Models::Town> town; // La ville dans laquelle se déroule la partie

	static LogicManager instance; // Instance unique du LogicManager

	// Cache de localisation pour plus facilement accéder aux bâtiments en fonction de leur emplacement
	// Liste des Buildings [x => [y => Building]]
	map<int, map<int, Models::Building*>> mapBuildingLocation;
};
