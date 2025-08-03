// medieval-town.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
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
*/
