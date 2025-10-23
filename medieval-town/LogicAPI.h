#pragma once
#include <string>

// Interface entre le LogicManager et le moteur de jeu. Déclaration minimale intégrant les méthode appelées par le LogicManager, et implémentation vide pour compiler sans erreur hors du moteur de jeu.
class LogicAPI
{
	public:
		// Log de debug
		void log(std::string message) {};
};

