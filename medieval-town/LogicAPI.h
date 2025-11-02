#pragma once
#include <string>

// Interface entre le LogicManager et le moteur de jeu. Déclaration minimale intégrant les méthode appelées par le LogicManager, et implémentation vide pour compiler sans erreur hors du moteur de jeu. Le nom "ALogicAPI" répond aux conventions d'Unreal Engine, mais le fichier reste nommé "LogicAPI.h".
class ALogicAPI
{
	public:
		// Log de debug
		void log(std::string message) {};
};

