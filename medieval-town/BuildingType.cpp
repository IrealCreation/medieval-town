#include "BuildingType.h"

namespace Models {
	BuildingType::BuildingType(const std::string& name, int goldConstructionCost, int goldMaintenanceCost,
		const std::map<Pop, int>& goldCostPerPopulation, const std::map<Pop, int>& goldGainPerPopulation,
		const std::map<Pop, int>& prestigeGainPerPopulation, int range, int maxCapacity,
		int constructionTime, Service serviceType)
		: name(name), goldConstructionCost(goldConstructionCost), goldMaintenanceCost(goldMaintenanceCost),
		goldCostPerPopulation(goldCostPerPopulation), goldGainPerPopulation(goldGainPerPopulation),
		prestigeGainPerPopulation(prestigeGainPerPopulation), range(range), maxCapacity(maxCapacity),
		constructionTime(constructionTime), service(service) {}

	// Constructeur minimal pour tests
	BuildingType::BuildingType(const std::string& name, int goldConstructionCost, int goldMaintenanceCost, int constructionTime, Service service)
		: name(name), goldConstructionCost(goldConstructionCost), goldMaintenanceCost(goldMaintenanceCost), constructionTime(constructionTime), service(service) {}

	std::string BuildingType::getName() const {
		return name;
	}
	int BuildingType::getGoldConstructionCost() const {
		return goldConstructionCost;
	}
	int BuildingType::getGoldMaintenanceCost() const {
		return goldMaintenanceCost;
	}
	int BuildingType::getGoldCostPerPopulation(Pop pop) const {
		if (!isPopServed(pop)) {
			return 0;
		}
		return goldCostPerPopulation.at(pop);
	}
	int BuildingType::getGoldGainPerPopulation(Pop pop) const {
		if (!isPopServed(pop)) {
			return 0;
		}
		return goldGainPerPopulation.at(pop);
	}
	int BuildingType::getPrestigeGainPerPopulation(Pop pop) const {
		if (!isPopServed(pop)) {
			return 0;
		}
		return prestigeGainPerPopulation.at(pop);
	}
	int BuildingType::getRange() const {
		return range;
	}
	int BuildingType::getMaxCapacity() const {
		return maxCapacity;
	}
	int BuildingType::getConstructionTime() const {
		return constructionTime;
	}
	const Service& BuildingType::getService() const {
		return service;
	}
	bool BuildingType::isPopServed(Pop pop) const {
		return goldCostPerPopulation.find(pop) != goldCostPerPopulation.end() &&
			goldGainPerPopulation.find(pop) != goldGainPerPopulation.end() &&
			prestigeGainPerPopulation.find(pop) != prestigeGainPerPopulation.end();
	}
} // namespace Models
