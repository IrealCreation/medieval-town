#pragma once
#include <string>
#include "Location.h" // Classe parent : on doit inclure son header

namespace Models
{
	// Forward declarations pour éviter les dépendances circulaires
	class Family;
	class BuildingType;

	class Building : public Location
	{
	public:
		Building(const BuildingType& type, Family* family, float x, float y, float rotation);
		void logicTick(); // Tick de progression du jeu appelé à chaque unité standard de temps (jour ?)

		std::string getName();
		void setName(const std::string& name);

	private:
		const BuildingType& type; // Un building ne change jamais de type, donc on le stocke par référence et en const
		Family* family; // Famille propriétaire du bâtiment ; nullptr si pas de propriétaire, donc on le stocke par pointeur
		std::string name; // Nom personnalisé du bâtiment (nom de son BuildingType sinon)
		int dateCreation; // Date de création du bâtiment (fin du chantier de construction)
	};
}

