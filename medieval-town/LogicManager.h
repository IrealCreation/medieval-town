#pragma once
#include <string>
#include <memory>
using std::unique_ptr;
using std::shared_ptr;
using std::string;

// Forward declarations pour �viter les d�pendances circulaires
namespace Models {
	class Town;
	class BuildingType;
	class Building;
	class Family;
	class Location;
	class Construction;
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

	// D�bute la construction d'un b�timent
	void startConstruction(const Models::BuildingType* type, Models::Family* family, int x, int y, int rotation);
	// Termine la construction d'un b�timent
	void constructionDone(Models::Construction* construction);

protected:
	LogicManager();

	unique_ptr<Models::Town> town; // La ville dans laquelle se d�roule la partie

	static LogicManager instance; // Instance unique du LogicManager
};
