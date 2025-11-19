#include "Building.h"
#include "BuildingType.h"
#include "Family.h"
#include "LogicManager.h"
#include "House.h"
#include "Town.h"
#include <map>
using std::map;

namespace Models {
	Building::Building(const BuildingType& type, Family* family, int32 x, int32 y, float rotation)
		: Location(x, y, rotation, type.getSizeX(), type.getSizeY()), type(type), family(family), name(type.getName()), dateCreation(0) 
	{
		// On initialise la date de création à la date actuelle de la ville
		dateCreation = LogicManager::getInstance().getTown()->getDate();

		// On trouve les maisons desservies par ce bâtiment
		// TEST: on appelle cette fonction dans le tick, donc pas besoin de le faire ici
		// this->updateHousesServed();
	}

	void Building::logicTick() {
		// TEST: on met à jour les maisons servies à chaque tick. Pas optimisé, à améliorer : update quand un bâtiment ou une maison est construite (TODO) ou détruite (DONE) à proximité
		//if(mustUpdateHousesServed)
			this->updateServed();
		mustUpdateServed = false;

		// Décompte des populations servies
		map<Pop, int32> totalPopsServed = {
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
			int32 totalGoldGain = 0;
			int32 totalPrestigeGain = 0;
			for (const auto& pair : totalPopsServed) {
				Pop pop = pair.first;
				int32 popCount = pair.second;
				totalGoldGain += popCount * type.getGoldGainPerPopulation(pop);
				totalPrestigeGain += popCount * type.getPrestigeGainPerPopulation(pop);
			}

			// On ajoute l'or et le prestige à la famille
			family->addGold(totalGoldGain);
			family->addPrestige(totalPrestigeGain);
		}
	}

	std::string Building::getName() {
		return name;
	}

	void Building::setName(const std::string& newName) {
		this->name = newName;
	}

	const BuildingType& Building::getType() const {
		return type;
	}

	Family* Building::getFamily() const {
		return family;
	}

	void Building::changeCapacityUsed(int32 delta) {
		capacityUsed += delta;
	}

	std::vector<House*> Building::getHousesServed() const {
		return housesServed;
	}
	void Building::removeHouseServed(House* house) {
		auto it = std::find(housesServed.begin(), housesServed.end(), house);
		if (it != housesServed.end()) {
			housesServed.erase(it);
			// Mise à jour de la capacité utilisée
			capacityUsed -= house->getPopTotal();
			// On doit update les maisons servies au prochain tick pour voir s'il y a des gens intéressés par les places libérées
			this->setMustUpdateServed();
		}
	}

	std::vector<Tile*> Building::getMarginalTilesServed() const {
		return marginalTilesServed;
	}

	void Building::updateServed() {
		// On récupère les maisons à portée
		auto houses = LogicManager::getInstance().getHousesInRange(this->getX(), this->getY(), this->type.getRange());

		// Nombre de places restantes dans le bâtiment
		int32 capacityLeft = this->type.getMaxCapacity() - capacityUsed;

		for (auto house : houses) {
			int32 housePop = house->getPopTotal();
			if (house->getServiceBuilding(this->type.getService()) == nullptr && housePop < capacityLeft) {
				// La maison n'a pas encore de bâtiment pour ce service, on la récupère dans notre clientèle
				house->addService(this->type.getService(), this);
				this->housesServed.push_back(house);
				// Mise à jour de la capacité utilisée
				capacityUsed += housePop;
				capacityLeft -= housePop;

				// Si on n'a plus de places, on arrête de chercher des maisons
				if (capacityLeft <= 0)
					break;
			}
		}

		if(capacityLeft > 0) {
			// Il reste de la capacité, on peut mettre à jour le service marginal, c'est-à-dire les House et les Tile qui peuvent bénéficier des services de ce bâtiment pour une nouvelle unité de population (permet le calcul de l'attractivité)
			
			// Maisons bénéficiant du service marginal
			marginalHousesServed.clear();
			for (auto house : houses) {
				marginalHousesServed.push_back(house);
				house->addMarginalService(this->type.getService(), this);
			}

			// Tiles bénéficiant du service marginal
			marginalTilesServed.clear();
			auto tiles = LogicManager::getInstance().getTilesInRange(this->getX(), this->getY(), this->type.getRange());
			for (auto tile : tiles) {
				marginalTilesServed.push_back(tile);
				tile->addMarginalService(this->type.getService(), this);
			}
		} else {
			// Pas de capacité restante : pas de service marginal
			for (auto house : marginalHousesServed) {
				house->removeMarginalService(this->type.getService(), this);
			}
			marginalHousesServed.clear();
			for (auto tile : marginalTilesServed) {
				tile->removeMarginalService(this->type.getService(), this);
			}
			marginalTilesServed.clear();
		}
	}
	void Building::setMustUpdateServed() {
		mustUpdateServed = true;
	}

} // namespace Models