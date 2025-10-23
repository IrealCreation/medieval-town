#pragma once
#include <string>

// Interface entre le LogicManager et le moteur de jeu. D�claration minimale int�grant les m�thode appel�es par le LogicManager, et impl�mentation vide pour compiler sans erreur hors du moteur de jeu.
class LogicAPI
{
	public:
		// Log de debug
		void log(std::string message) {};
};

