// medieval-town.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "LogicManager.h"
LogicManager LogicManager::instance; // Instanciation du LogicManager
#include "Family.h"
#include "Town.h"
#include "BuildingType.h"
#include <memory>
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::make_shared;

#include <windows.h> // Ajout nécessaire pour SetConsoleOutputCP et CP_UTF8

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "Lancement de Medieval Town\n";

    LogicManager& logicManager = LogicManager::getInstance();

    logicManager.startGame();

	std::cout << "La ville " << logicManager.getTown()->getName() << " a été créée avec succès.\n";

    std::wcout << "Familles en jeu : ";
    bool* first = new bool(true); // Smart pointer qu'on supprimera juste après la boucle
    for (const auto family : logicManager.getTown()->getFamilies()) {
        
        std::cout << (*first ? "" : ", ") << family->getName();
        *first = false;
    }
    delete first;
    std::cout << "\n";

	// Initialisation du BuildingType Chapelle
    std::map<Models::Pop, int> goldCostPerPopulation = {
        { Models::Pop::Gueux, 0 },
        { Models::Pop::Bourgeois, 0 },
        { Models::Pop::Noble, 0 }
	};
    std::map<Models::Pop, int> goldGainPerPopulation = {
        { Models::Pop::Gueux, 2 },
        { Models::Pop::Bourgeois, 3 },
        { Models::Pop::Noble, 4 }
	};
    std::map<Models::Pop, int> prestigeGainPerPopulation = {
        { Models::Pop::Gueux, 2 },
        { Models::Pop::Bourgeois, 4 },
		{ Models::Pop::Noble, 6 }
	};
	unique_ptr<Models::BuildingType> buildingType_Chapelle = make_unique<Models::BuildingType>(
        "Chapelle", 
        5, 5,
        200, 20, 
        goldCostPerPopulation,
        goldGainPerPopulation, 
        prestigeGainPerPopulation, 
        10, 50, 5, 
        Models::Service::Priere
    );

    // Initialisation du BuildingType Puits
    goldCostPerPopulation = {
        { Models::Pop::Gueux, 0 },
        { Models::Pop::Bourgeois, 0 },
        { Models::Pop::Noble, 0 }
    };
    goldGainPerPopulation = {
        { Models::Pop::Gueux, 1 },
        { Models::Pop::Bourgeois, 1 },
        { Models::Pop::Noble, 1 }
    };
    prestigeGainPerPopulation = {
        { Models::Pop::Gueux, 3 },
        { Models::Pop::Bourgeois, 3 },
        { Models::Pop::Noble, 3 }
    };
    unique_ptr<Models::BuildingType> buildingType_Puits = make_unique<Models::BuildingType>(
        "Puits",
        2, 2,
        50, 5,
        goldCostPerPopulation,
        goldGainPerPopulation,
        prestigeGainPerPopulation,
        8, 40, 3,
        Models::Service::Eau
    );

    // Construction d'un bâtiment : Puits par Salviati
    logicManager.startConstructionBuilding(*buildingType_Puits, logicManager.getTown()->getFamilies()[0], 10, 5, 0);
	// Construction d'un bâtiment : Chapelle par Legrand
	logicManager.startConstructionBuilding(*buildingType_Chapelle, logicManager.getTown()->getFamilies()[1], 10, 15, 0);

    int i = 0;
    // Boucle des ticks tant que le joueur presse Entrée
    do
    {
        logicManager.logicTick();

        // On fait spawn une maison tous les deux ticks sur une ligne (test)
        if (logicManager.getTown()->getDate() % 2 == 0) {
            logicManager.startConstructionHouse(i + 5, 10, 0, 2, 2, 1);
        }

        i++;
    } while (std::cin.get() == '\n');
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

/*
Quand stocker une valeur dans une propriété d'une classe en valeur / référence / pointeur ?
    Valeur : quand cette classe stocke la version "originale" de l'objet et qu'elle manage son cycle de vie, ou qu'elle doit en conserver une copie indépendante du contexte extérieur
    Référence : quand cette classe ne stocke pas la version "originale" ni une copie indépendante, que la propriété est non-nullable et ne changera pas de valeur pour un autre objet différent
    Pointeur : quand cette propriété est nullable et/ou qu'on doit pouvoir la switcher vers un autre objet
Ne pas stocker une enum par référence dans une propriété de classe
*/

/*
Pointeurs
    Quand un pointer est créé avec "new", il DOIT être manuellement détruit avec "delete", sinon on a un memory leak
    Smart pointer : 
        Pointeur unique (une seule variable à la fois a le droit de le posséder) : std::unique_ptr<MonType> monPointeurUnique = std::make_unique<MonType>(mesArguments)
            Pour déplacer cet unique_ptr : std::move(monPointeurUnique)
        Pointeur partagé (peut être possédé par plusieurs variables) : std::shared_ptr<MonType> monPointeurPartage = std::make_shared<MonType>(mesArguments)
        Quand plus personne ne référence mon instance avec un unique_ptr ni un shared_ptr, elle est détruite
        Les unique_ptr sont beaucoup plus efficients que shared_ptr, les privilégier quand on le peut
        Pour utiliser les smart pointers, il faut include <memory>
*/
