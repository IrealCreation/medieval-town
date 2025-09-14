#include "Building.h"
#include "BuildingType.h"
#include "Family.h"
#include "LogicManager.h"
#include "House.h"
#include "Town.h"
#include <map>
using std::map;

namespace Models {
	Building::Building(const BuildingType& type, Family* family, float x, float y, float rotation)
		: Location(x, y, rotation), type(type), family(family), name(type.getName()), dateCreation(0) 
	{
		// On initialise la date de création à la date actuelle de la ville
		dateCreation = LogicManager::getInstance().getTown()->getDate();

		// On trouve les maisons desservies par ce bâtiment
		this->updateHousesServed();
	}

	void Building::logicTick() {
		// Décompte des populations servies
		map<Pop, int> totalPopsServed = {
			{ Pop::Gueux, 0 },
			{ Pop::Bourgeois, 0 },
			{ Pop::Noble, 0 }
		};
		for (auto house : housesServed) {
			// On ajoute les pops de la maison à notre total
			for (const auto& pair : totalPopsServed) {
				totalPopsServed[pair.first] += house->getPop(pair.first);
			}
		}

		if (family) {
			// Le bâtiment a une famille propriétaire
			// Maintenance du bâtiment
			family->removeGold(type.getGoldMaintenanceCost());

			// Gain d'or et de prestige grâce aux pops servies
			int totalGoldGain = 0;
			int totalPrestigeGain = 0;
			for (const auto& pair : totalPopsServed) {
				Pop pop = pair.first;
				int popCount = pair.second;
				totalGoldGain += popCount * type.getGoldGainPerPopulation(pop);
				totalPrestigeGain += popCount * type.getPrestigeGainPerPopulation(pop);
			}
		}
	}

	std::string Building::getName() {
		return name;
	}

	void Building::setName(const std::string& name) {
		this->name = name;
	}

	void Building::updateHousesServed() {
		// On récupère les maisons à portée
		auto houses = LogicManager::getInstance().getHousesInRange(this->getX(), this->getY(), this->type.getRange());

		// Nombre de places restantes dans le bâtiment
		int capacityLeft = this->type.getMaxCapacity();

		for (auto house : houses) {
			int housePop = house->getPopTotal();
			if (house->getServiceBuilding(this->type.getService()) == nullptr && housePop < capacityLeft) {
				// La maison n'a pas encore de bâtiment pour ce service, on la récupère dans notre clientèle
				house->addService(this->type.getService(), this);
				this->housesServed.push_back(house);
				capacityLeft -= housePop;

				// Si on n'a plus de places, on arrête de chercher des maisons
				if (capacityLeft <= 0)
					break;
			}
		}
	}

} // namespace Models