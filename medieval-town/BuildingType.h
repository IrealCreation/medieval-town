#pragma once
#include <string>
#include <map>
#include <vector>
#include "Pop.h"
#include "Service.h"
#include "Resource.h"
#include "ProductionCycle.h"
#include <cstdint>
using int32 = int32_t; // Match le type "int" d'Unreal Engine

namespace Models {
	// Type de bâtiment pouvant être construit dans la ville
	class BuildingType {
	public:
		BuildingType(const std::string& id, const std::string& name, int32 sizeX, int32 sizeY, int32 goldConstructionCost, int32 goldMaintenanceCost,
			const std::map<Pop, int32>& goldCostPerPopulation, 
			const std::map<Pop, int32>& goldGainPerPopulation,
			const std::map<Pop, int32>& prestigeGainPerPopulation, 
			const std::map<Pop, std::map<Resource, int32>>& resourcesCostPerPopulation,
			int32 range, int32 maxCapacity,
			int32 constructionTime, Service service);

		// Getters
		std::string getId() const; // ID unique utilisé dans la communication avec le moteur de jeu
		std::string getName() const; // Nom affiché au joueur
		int32 getSizeX() const;
		int32 getSizeY() const;
		int32 getGoldConstructionCost() const;
		int32 getGoldMaintenanceCost() const;
		int32 getGoldCostPerPopulation(Pop) const;
		int32 getGoldGainPerPopulation(Pop) const;
		int32 getPrestigeGainPerPopulation(Pop) const;
		std::map<Resource, int32> getResourcesCostPerPopulation(Pop) const;
		int32 getRange() const;
		int32 getMaxCapacity() const;
		int32 getConstructionTime() const; // Temps de construction du bâtiment, en jours
		const Service& getService() const;
		bool isPopServed(Pop pop) const; // Cette pop est-elle servie par le batiment ?

		void addProductionCycle(const ProductionCycle cycle); // Ajoute un cycle de production au bâtiment
		const std::vector<ProductionCycle>& getProductionCycles() const; // Retourne les cycles de production du bâtiment

	protected:
		const std::string id = ""; // Identifiant unique du type de batiment
		std::string name = ""; // Nom du type de batiment
		int32 sizeX = 0; // Taille totale du bâtiment sur l'axe X
		int32 sizeY = 0; // Taille totale du bâtiment sur l'axe Y
		int32 goldConstructionCost = 0; // Coût de construction en or
		int32 goldMaintenanceCost = 0; // Coût d'entretien en or
		std::map<Pop, int32> goldCostPerPopulation = {}; // Coût en or par population servie
		std::map<Pop, int32> goldGainPerPopulation = {}; // Quantité d'or gagnée par population servie
		std::map<Pop, int32> prestigeGainPerPopulation = {}; // Quantité de prestige gagnée par population servie
		std::map<Pop, std::map<Resource, int32>> resourcesCostPerPopulation = {}; // Ressources consommées par population servie
		int32 range = 0; // Rayon d'action du bâtiment, en mètres à partir de son point d'origine
		int32 maxCapacity = 0; // Nombre maximum de pops (toutes confondues) servies par ce bâtiment
		int32 constructionTime = 0; // Temps de construction du bâtiment, en jours
		const Service service = {}; // Type de service fourni par le bâtiment

		std::vector<ProductionCycle> productionCycles = {}; // Cycles de production du bâtiment (s'il en a)
	};
}