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

// Forward declarations pour �viter les d�pendances circulaires
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

// Le GameManager remplit deux utilis�s : servir de chef d'orchestre entre toutes les classes Models ; et servir de point d'interaction entre les classes Models et le moteur de jeu
class LogicManager
{

public:
	// On supprime l'op�rateur de copie pour ne pas que notre instance soit dupliqu�e
	LogicManager(const LogicManager&) = delete;

	// R�f�rence au GameManager unique de la partie
	static LogicManager& getInstance();

	// D�but de la partie
	void startGame();

	// Tick de progression du jeu appel� � chaque unit� standard de temps (jour ?)
	void logicTick();

	// Log de debug
	void log(string message);

	// Retourne un raw pointer vers la ville ; le cycle de vie de la ville reste g�r� par le LogicManager
	Models::Town* getTown();

	// D�bute la construction d'un b�timent de service
	void startConstructionBuilding(const Models::BuildingType& type, Models::Family* family, int x, int y, int rotation);
	// Termine la construction d'un b�timent de service
	void constructionBuildingDone(Models::ConstructionBuilding* construction);
	// Ajoute un b�timent de service achev�
	void createBuilding(const Models::BuildingType& type, Models::Family* family, int x, int y, int rotation);
	// D�truire un b�timent de service
	void destroyBuilding(Models::Building* building);

	// D�bute la construction d'une maison d'habitation
	void startConstructionHouse(int x, int y, int rotation, int sizeX, int sizeY, int niveau);
	// Termine la construction d'une maison d'habitation
	void constructionHouseDone(Models::ConstructionHouse* construction);
	// Ajoute une maison d'habitation achev�e
	void createHouse(int x, int y, int rotation, int sizeX, int sizeY, int niveau);
	// D�truire une maison d'habitation
	void destroyHouse(Models::House* house);

	// R�cup�re les maisons situ�es dans un rayon donn� autour d'un point (ordonn�es de la plus proche � la plus �loign�e)
	vector<Models::House*> getHousesInRange(int x, int y, int range);
	// R�cup�re les tiles situ�s dans un rayon donn� autour d'un point (non ordonn�s)
	vector<Models::Tile*> getTilesInRange(int x, int y, int range);


protected:
	LogicManager();

	unique_ptr<Models::Town> town; // La ville dans laquelle se d�roule la partie

	static LogicManager instance; // Instance unique du LogicManager

	// Cache de localisation pour plus facilement acc�der aux �l�ments en fonction de leur emplacement
	// Liste de toutes les Locations [x => [y => Location*]]
	map<int, map<int, Models::Location*>> mapLocations;
	// Liste des Buildings [x => [y => Building*]]
	map<int, map<int, Models::Building*>> mapBuildings;
	// Liste des Houses [x => [y => House*]]
	map<int, map<int, Models::House*>> mapHouses;

	// Fonction permettant de r�cup�rer les �l�ments des caches de localisation siti�es dans un rayon donn� autour d'un point (ordonn�es de la plus proche � la plus �loign�e)
	// TODO: essayer d'�viter la duplication de code dans les fonctions getXInRange, genre avec un template et un static_assert( std::is_base_of<> ... ) ?
	// (Rappel : comme le C++ est un langage qui aime les blagues, on ne peut pas d�clarer de templates dans le header)
	/* 
	template<typename T>
	vector<T*> getInRange(int x, int y, int range, map<int, map<int, T>>);
	*/
};
