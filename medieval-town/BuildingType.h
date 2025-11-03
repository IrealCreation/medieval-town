#pragma once
#include <string>
#include <map>
#include "Pop.h"
#include "Service.h"
#include <cstdint>
using int32 = uint32_t; // Match le type "int" d'Unreal Engine

namespace Models {
	// Type de bâtiment pouvant être construit dans la ville
	class BuildingType {
	public:
		BuildingType(const std::string& id, const std::string& name, float sizeX, float sizeY, int32 goldConstructionCost, int32 goldMaintenanceCost,
			const std::map<Pop, int32>& goldCostPerPopulation, const std::map<Pop, int32>& goldGainPerPopulation,
			const std::map<Pop, int32>& prestigeGainPerPopulation, int32 range, int32 maxCapacity,
			int32 constructionTime, Service service);

		// Getters
		std::string getId() const; // ID unique utilisé dans la communication avec le moteur de jeu
		std::string getName() const; // Nom affiché au joueur
		float getSizeX() const;
		float getSizeY() const;
		int32 getGoldConstructionCost() const;
		int32 getGoldMaintenanceCost() const;
		int32 getGoldCostPerPopulation(Pop) const;
		int32 getGoldGainPerPopulation(Pop) const;
		int32 getPrestigeGainPerPopulation(Pop) const;
		int32 getRange() const;
		int32 getMaxCapacity() const;
		int32 getConstructionTime() const; // Temps de construction du bâtiment, en jours
		const Service& getService() const;
		bool isPopServed(Pop pop) const; // Cette pop est-elle servie par le batiment ?

	protected:
		const std::string id; // Identifiant unique du type de batiment
		std::string name; // Nom du type de batiment
		float sizeX; // Taille totale du bâtiment sur l'axe X
		float sizeY; // Taille totale du bâtiment sur l'axe Y	
		int32 goldConstructionCost; // Coût de construction en or
		int32 goldMaintenanceCost; // Coût d'entretien en or
		std::map<Pop, int32> goldCostPerPopulation; // Coût en or par population servie
		// TODO: coutRessourceParPop
		std::map<Pop, int32> goldGainPerPopulation; // Quantité d'or gagnée par population servie
		std::map<Pop, int32> prestigeGainPerPopulation; // Quantité de prestige gagnée par population servie
		int32 range; // Portée d'action du bâtiment, en mètres
		int32 maxCapacity; // Nombre maximum de pops (toutes confondues) servies par ce bâtiment
		int32 constructionTime; // Temps de construction du bâtiment, en jours
		const Service service; // Type de service fourni par le bâtiment
	};
}