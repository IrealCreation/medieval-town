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
#include <cstdint>
using int32 = uint32_t; // Match le type "int" d'Unreal Engine

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
class ALogicAPI;

// Le GameManager remplit deux utilisés : servir de chef d'orchestre entre toutes les classes Models ; et servir de point d'interaction entre les classes Models et le moteur de jeu
class LogicManager
{

public:
	// On supprime l'opérateur de copie pour ne pas que notre instance soit dupliquée
	LogicManager(const LogicManager&) = delete;

	// Référence au GameManager unique de la partie
	static LogicManager& getInstance();

	// Définit l'interface avec le moteur de jeu 
	void setAPI(ALogicAPI* newApi);

	// Début de la partie
	void startGame();

	// Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)
	void logicTick();

	// Log de debug
	void log(string message) const;

	// Retourne un raw pointer vers la ville ; le cycle de vie de la ville reste géré par le LogicManager
	Models::Town* getTown();

	// Ajoute une famille à partie, et renvoie son ID
	int32 addFamily(const string& name);

	// Initialise les BuildingTypes
	void initBuildingTypes();

	// Retourne un raw pointer vers le BuildingType correspondant à l'ID donné ; nullptr si pas trouvé
	Models::BuildingType* getBuildingType(const string& id);

	// Débute la construction d'un bâtiment de service
	void startConstructionBuilding(const Models::BuildingType& type, Models::Family* family, int32 x, int32 y, int32 rotation);
	// Débute la construction d'un bâtiment de service (surcharge avec l'ID du BuildingType et de la Family)
	void startConstructionBuilding(const string& buildingTypeId, int32 familyId, int32 x, int32 y, int32 rotation);
	// Termine la construction d'un bâtiment de service
	void constructionBuildingDone(Models::ConstructionBuilding* construction);
	// Ajoute un bâtiment de service achevé
	void createBuilding(const Models::BuildingType& type, Models::Family* family, int32 x, int32 y, int32 rotation);
	// Détruire un bâtiment de service
	void destroyBuilding(Models::Building* building);

	// Débute la construction d'une maison d'habitation
	void startConstructionHouse(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau);
	// Termine la construction d'une maison d'habitation
	void constructionHouseDone(Models::ConstructionHouse* construction);
	// Ajoute une maison d'habitation achevée
	void createHouse(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau);
	// Détruire une maison d'habitation
	void destroyHouse(Models::House* house);

	Models::Location* getLocationAt(int32 x, int32 y); // Retourne un raw pointer vers la Location à la position donnée ; nullptr si pas de Location

	// Récupère les maisons situées dans un rayon donné autour d'un point (ordonnées de la plus proche à la plus éloignée)
	vector<Models::House*> getHousesInRange(int32 x, int32 y, int32 range);
	// Récupère les tiles situés dans un rayon donné autour d'un point (non ordonnés)
	vector<Models::Tile*> getTilesInRange(int32 x, int32 y, int32 range);

	// Vérifie si une Location peut être placée à cet endroit (collision avec d'autres Locations)
	bool isValidLocation(float x, float y, float rotation, float sizeX, float sizeY); 

	// Ajoute un tile dans la liste des candidats pour la construction d'une maison
	void addPossibleHouseLocation(Models::Tile* tile);
	// Retire un tile de la liste des candidats pour la construction d'une maison
	void removePossibleHouseLocation(Models::Tile* tile);

	// Sélectionne le prochain emplacement de construction d'une nouvelle maison
	Models::Tile* pickPossibleHouseLocation();

protected:
	LogicManager();

	unique_ptr<Models::Town> town; // La ville dans laquelle se déroule la partie

	static LogicManager instance; // Instance unique du LogicManager

	// Liste des BuildingTypes avec leur ID comme clé
	map<string, unique_ptr<Models::BuildingType>> buildingTypes;

	// Ajoute un BuildingType à la liste
	void addBuildingType(unique_ptr<Models::BuildingType> buildingType);

	// Cache de localisation pour plus facilement accéder aux éléments en fonction de leur emplacement
	// Liste de toutes les Locations [x => [y => Location*]]
	map<int32, map<int32, Models::Location*>> mapLocations;
	// Liste des Buildings [x => [y => Building*]]
	map<int32, map<int32, Models::Building*>> mapBuildings;
	// Liste des Houses [x => [y => House*]]
	map<int32, map<int32, Models::House*>> mapHouses;

	// Fonction permettant de récupérer les éléments des caches de localisation sitiées dans un rayon donné autour d'un point (ordonnées de la plus proche à la plus éloignée)
	// TODO: essayer d'éviter la duplication de code dans les fonctions getXInRange, genre avec un template et un static_assert( std::is_base_of<> ... ) ?
	// (Rappel : comme le C++ est un langage qui aime les blagues, on ne peut pas déclarer de templates dans le header)
	/* 
	template<typename T>
	vector<T*> getInRange(int32 x, int32 y, int32 range, map<int32, map<int32, T>>);
	*/

	// Met à jour les tiles autour de la location d'une construction pour indiquer qu'ils ne peuvent plus recevoir de maison
	void updateCanHaveHouseAroundConstruction(Models::Location* location); 

	// Met à jour les tiles autour de la location d'une destruction pour indiquer qu'ils peuvent à nouveau recevoir une maison
	void updateCanHaveHouseAroundDestruction(Models::Location* location); 
	
	// Liste des tiles candidats pour la construction d'une maison (canHaveHouse == true et attractiveness > 0)
	vector<Models::Tile*> possibleHouseLocations; 

private:
	ALogicAPI* api; // Interface avec le moteur de jeu (nullptr si on n'est pas dans le moteur)
};
