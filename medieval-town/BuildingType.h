#pragma once
#include <string>
#include <map>
#include "Pop.h"
#include "Service.h"

namespace Models {
	// Type de bâtiment pouvant être construit dans la ville
	class BuildingType {
	public:
		BuildingType(const std::string& name, float sizeX, float sizeY, int goldConstructionCost, int goldMaintenanceCost,
			const std::map<Pop, int>& goldCostPerPopulation, const std::map<Pop, int>& goldGainPerPopulation,
			const std::map<Pop, int>& prestigeGainPerPopulation, int range, int maxCapacity,
			int constructionTime, Service service);

		// Getters
		virtual std::string getName() const;
		float getSizeX() const;
		float getSizeY() const;
		virtual int getGoldConstructionCost() const;
		virtual int getGoldMaintenanceCost() const;
		virtual int getGoldCostPerPopulation(Pop) const;
		virtual int getGoldGainPerPopulation(Pop) const;
		virtual int getPrestigeGainPerPopulation(Pop) const;
		virtual int getRange() const;
		virtual int getMaxCapacity() const;
		virtual int getConstructionTime() const; // Temps de construction du bâtiment, en jours
		const Service& getService() const;
		virtual bool isPopServed(Pop pop) const; // Cette pop est-elle servie par le batiment ?

	protected:
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