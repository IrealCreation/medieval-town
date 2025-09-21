#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>
using std::unique_ptr;
using std::shared_ptr;
using std::string;
using std::map;
using std::vector;

// Forward declarations pour éviter les dépendances circulaires
namespace Models {
	class Town;
	class BuildingType;
	class Building;
	class House;
	class Family;
	class Location;
	class Tile;
	class Construction;
	class ConstructionBuilding;
	class ConstructionHouse;
}

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

	// Débute la construction d'un bâtiment de service
	void startConstructionBuilding(const Models::BuildingType& type, Models::Family* family, int x, int y, int rotation);
	// Termine la construction d'un bâtiment de service
	void constructionBuildingDone(Models::ConstructionBuilding* construction);
	// Ajoute un bâtiment de service achevé
	void createBuilding(const Models::BuildingType& type, Models::Family* family, int x, int y, int rotation);
	// Détruire un bâtiment de service
	void destroyBuilding(Models::Building* building);

	// Débute la construction d'une maison d'habitation
	void startConstructionHouse(int x, int y, int rotation, int sizeX, int sizeY, int niveau);
	// Termine la construction d'une maison d'habitation
	void constructionHouseDone(Models::ConstructionHouse* construction);
	// Ajoute une maison d'habitation achevée
	void createHouse(int x, int y, int rotation, int sizeX, int sizeY, int niveau);
	// Détruire une maison d'habitation
	void destroyHouse(Models::House* house);

	// Récupère les maisons situées dans un rayon donné autour d'un point (ordonnées de la plus proche à la plus éloignée)
	vector<Models::House*> getHousesInRange(int x, int y, int range);
	// Récupère les tiles situés dans un rayon donné autour d'un point (non ordonnés)
	vector<Models::Tile*> getTilesInRange(int x, int y, int range);


protected:
	LogicManager();

	unique_ptr<Models::Town> town; // La ville dans laquelle se déroule la partie

	static LogicManager instance; // Instance unique du LogicManager

	// Cache de localisation pour plus facilement accéder aux éléments en fonction de leur emplacement
	// Liste de toutes les Locations [x => [y => Location*]]
	map<int, map<int, Models::Location*>> mapLocations;
	// Liste des Buildings [x => [y => Building*]]
	map<int, map<int, Models::Building*>> mapBuildings;
	// Liste des Houses [x => [y => House*]]
	map<int, map<int, Models::House*>> mapHouses;

	// Fonction permettant de récupérer les éléments des caches de localisation sitiées dans un rayon donné autour d'un point (ordonnées de la plus proche à la plus éloignée)
	// TODO: essayer d'éviter la duplication de code dans les fonctions getXInRange, genre avec un template et un static_assert( std::is_base_of<> ... ) ?
	// (Rappel : comme le C++ est un langage qui aime les blagues, on ne peut pas déclarer de templates dans le header)
	/* 
	template<typename T>
	vector<T*> getInRange(int x, int y, int range, map<int, map<int, T>>);
	*/
};
