#pragma once
#include <string>
#include <map>
#include "Pop.h"
#include "Service.h"

namespace Models {
	// Type de bâtiment pouvant être construit dans la ville
	class BuildingType {
	public:
		BuildingType(const std::string& id, const std::string& name, float sizeX, float sizeY, int goldConstructionCost, int goldMaintenanceCost,
			const std::map<Pop, int>& goldCostPerPopulation, const std::map<Pop, int>& goldGainPerPopulation,
			const std::map<Pop, int>& prestigeGainPerPopulation, int range, int maxCapacity,
			int constructionTime, Service service);

		// Getters
		std::string getId() const; // ID unique utilisé dans la communication avec le moteur de jeu
		std::string getName() const; // Nom affiché au joueur
		float getSizeX() const;
		float getSizeY() const;
		int getGoldConstructionCost() const;
		int getGoldMaintenanceCost() const;
		int getGoldCostPerPopulation(Pop) const;
		int getGoldGainPerPopulation(Pop) const;
		int getPrestigeGainPerPopulation(Pop) const;
		int getRange() const;
		int getMaxCapacity() const;
		int getConstructionTime() const; // Temps de construction du bâtiment, en jours
		const Service& getService() const;
		bool isPopServed(Pop pop) const; // Cette pop est-elle servie par le batiment ?

	protected:
		const std::string id; // Identifiant unique du type de batiment
		std::string name; // Nom du type de batiment
		float sizeX; // Taille totale du bâtiment sur l'axe X
		float sizeY; // Taille totale du bâtiment sur l'axe Y	
		int goldConstructionCost; // Coût de construction en or
		int goldMaintenanceCost; // Coût d'entretien en or
		std::map<Pop, int> goldCostPerPopulation; // Coût en or par population servie
		// TODO: coutRessourceParPop
		std::map<Pop, int> goldGainPerPopulation; // Quantité d'or gagnée par population servie
		std::map<Pop, int> prestigeGainPerPopulation; // Quantité de prestige gagnée par population servie
		int range; // Portée d'action du bâtiment, en mètres
		int maxCapacity; // Nombre maximum de pops (toutes confondues) servies par ce bâtiment
		int constructionTime; // Temps de construction du bâtiment, en jours
		const Service service; // Type de service fourni par le bâtiment
	};
}