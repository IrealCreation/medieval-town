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
		: Location(x, y, rotation, type.getSizeX(), type.getSizeY()), type(type), family(family), name(type.getName()), dateCreation(0) 
	{
		// On initialise la date de cr�ation � la date actuelle de la ville
		dateCreation = LogicManager::getInstance().getTown()->getDate();

		// On trouve les maisons desservies par ce b�timent
		// TEST: on appelle cette fonction dans le tick, donc pas besoin de le faire ici
		// this->updateHousesServed();
	}

	void Building::logicTick() {
		// TEST: on met � jour les maisons servies � chaque tick. Pas optimis�, � am�liorer : update quand un b�timent ou une maison est construite (TODO) ou d�truite (DONE) � proximit�
		//if(mustUpdateHousesServed)
			this->updateServed();
		mustUpdateServed = false;

		// D�compte des populations servies
		map<Pop, int> totalPopsServed = {
			{ Pop::Gueux, 0 },
			{ Pop::Bourgeois, 0 },
			{ Pop::Noble, 0 }
		};
		for (auto house : housesServed) {
			// On ajoute les pops de la maison � notre total
			for (const auto& pair : totalPopsServed) {
				totalPopsServed[pair.first] += house->getPop(pair.first);
			}
		}

		if (family) {

			// Le b�timent a une famille propri�taire
			// Maintenance du b�timent
			family->removeGold(type.getGoldMaintenanceCost());

			// Gain d'or et de prestige gr�ce aux pops servies
			int totalGoldGain = 0;
			int totalPrestigeGain = 0;
			for (const auto& pair : totalPopsServed) {
				Pop pop = pair.first;
				int popCount = pair.second;
				totalGoldGain += popCount * type.getGoldGainPerPopulation(pop);
				totalPrestigeGain += popCount * type.getPrestigeGainPerPopulation(pop);
			}

			// On ajoute l'or et le prestige � la famille
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

	void Building::changeCapacityUsed(int delta) {
		capacityUsed += delta;
	}

	std::vector<House*> Building::getHousesServed() const {
		return housesServed;
	}
	void Building::removeHouseServed(House* house) {
		auto it = std::find(housesServed.begin(), housesServed.end(), house);
		if (it != housesServed.end()) {
			housesServed.erase(it);
			// Mise � jour de la capacit� utilis�e
			capacityUsed -= house->getPopTotal();
			// On doit update les maisons servies au prochain tick pour voir s'il y a des gens int�ress�s par les places lib�r�es
			this->setMustUpdateServed();
		}
	}

	std::vector<Tile*> Building::getMarginalTilesServed() const {
		return marginalTilesServed;
	}

	void Building::updateServed() {
		// On r�cup�re les maisons � port�e
		auto houses = LogicManager::getInstance().getHousesInRange(this->getX(), this->getY(), this->type.getRange());

		// Nombre de places restantes dans le b�timent
		int capacityLeft = this->type.getMaxCapacity() - capacityUsed;

		for (auto house : houses) {
			int housePop = house->getPopTotal();
			if (house->getServiceBuilding(this->type.getService()) == nullptr && housePop < capacityLeft) {
				// La maison n'a pas encore de b�timent pour ce service, on la r�cup�re dans notre client�le
				house->addService(this->type.getService(), this);
				this->housesServed.push_back(house);
				// Mise � jour de la capacit� utilis�e
				capacityUsed += housePop;
				capacityLeft -= housePop;

				// Si on n'a plus de places, on arr�te de chercher des maisons
				if (capacityLeft <= 0)
					break;
			}
		}

		if(capacityLeft > 0) {
			// Il reste de la capacit�, on peut mettre � jour le service marginal, c'est-�-dire les House et les Tile qui peuvent b�n�ficier des services de ce b�timent pour une nouvelle unit� de population (permet le calcul de l'attractivit�)
			
			// Maisons b�n�ficiant du service marginal
			marginalHousesServed.clear();
			for (auto house : houses) {
				marginalHousesServed.push_back(house);
				house->addMarginalService(this->type.getService(), this);
			}

			// Tiles b�n�ficiant du service marginal
			marginalTilesServed.clear();
			auto tiles = LogicManager::getInstance().getTilesInRange(this->getX(), this->getY(), this->type.getRange());
			for (auto tile : tiles) {
				marginalTilesServed.push_back(tile);
				tile->addMarginalService(this->type.getService(), this);
			}
		} else {
			// Pas de capacit� restante : pas de service marginal
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