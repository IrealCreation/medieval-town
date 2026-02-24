#pragma once
#include <string>
#include <cstdint>
using int32 = int32_t; // Match le type "int" d'Unreal Engine

// Interface entre le LogicManager et le moteur de jeu. Déclaration minimale intégrant les méthode appelées par le LogicManager, et implémentation vide pour compiler sans erreur hors du moteur de jeu. Le nom "ALogicAPI" répond aux conventions d'Unreal Engine, mais le fichier reste nommé "LogicAPI.h".
class ALogicAPI
{
	public:
		// Log de debug
		void log(std::string message) {
			// Implémentation vide pour compiler sans erreur hors du moteur de jeu
		};

		// Retourne un entier aléatoire entre min et max inclus
		int32 RandRange(int32 min, int32 max) {
			// Implémentation vide pour compiler sans erreur hors du moteur de jeu
			return min;
		};
		// Retourne un float aléatoire entre min et max inclus
		float RandRange(float min, float max) {
			// Implémentation vide pour compiler sans erreur hors du moteur de jeu
			return min;
		};

		// Spawn a construction in the world
		void spawnConstruction(const Models::BuildingType& type, int32 x, int32 y, int32 rot) {}
		// Spawn a building in the world
		void spawnBuilding(const Models::BuildingType& type, int32 x, int32 y, int32 rot) {}
		// Spawn a house construction in the world
		void spawnHouseConstruction(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau) {}
		// Spawn a house in the world
		void spawnHouse(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau) {}

		// Adding such an important line.
};

