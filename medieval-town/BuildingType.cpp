#include "BuildingType.h"

namespace Models {
	BuildingType::BuildingType(const std::string& id, const std::string& name, float sizeX, float sizeY, int32 goldConstructionCost, int32 goldMaintenanceCost,
		const std::map<Pop, int32>& goldCostPerPopulation, const std::map<Pop, int32>& goldGainPerPopulation,
		const std::map<Pop, int32>& prestigeGainPerPopulation, int32 range, int32 maxCapacity,
		int32 constructionTime, Service service)
		: id(id), name(name), sizeX(sizeX), sizeY(sizeY), goldConstructionCost(goldConstructionCost), goldMaintenanceCost(goldMaintenanceCost),
		goldCostPerPopulation(goldCostPerPopulation), goldGainPerPopulation(goldGainPerPopulation),
		prestigeGainPerPopulation(prestigeGainPerPopulation), range(range), maxCapacity(maxCapacity),
		constructionTime(constructionTime), service(service) {}

	std::string BuildingType::getId() const {
		return id;
	}
	std::string BuildingType::getName() const {
		return name;
	}
	float BuildingType::getSizeX() const {
		return sizeX;
	}
	float BuildingType::getSizeY() const {
		return sizeY;
	}
	int32 BuildingType::getGoldConstructionCost() const {
		return goldConstructionCost;
	}
	int32 BuildingType::getGoldMaintenanceCost() const {
		return goldMaintenanceCost;
	}
	int32 BuildingType::getGoldCostPerPopulation(Pop pop) const {
		if (!isPopServed(pop)) {
			return 0;
		}
		return goldCostPerPopulation.at(pop);
	}
	int32 BuildingType::getGoldGainPerPopulation(Pop pop) const {
		if (!isPopServed(pop)) {
			return 0;
		}
		return goldGainPerPopulation.at(pop);
	}
	int32 BuildingType::getPrestigeGainPerPopulation(Pop pop) const {
		if (!isPopServed(pop)) {
			return 0;
		}
		return prestigeGainPerPopulation.at(pop);
	}
	int32 BuildingType::getRange() const {
		return range;
	}
	int32 BuildingType::getMaxCapacity() const {
		return maxCapacity;
	}
	int32 BuildingType::getConstructionTime() const {
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
