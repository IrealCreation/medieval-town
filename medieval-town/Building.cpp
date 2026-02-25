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

		// Génération de l'ID
		setId(type.getName(), dateCreation);

		// On trouve les maisons desservies par ce bâtiment
		// TEST: on appelle cette fonction dans le tick, donc pas besoin de le faire ici
		// this->updateHousesServed();
	}

	void Building::logicTick_production(int32 queue) {
		for(auto& cycle : type.getProductionCycles()) {
			if(cycle.getQueue() == queue) {
				// C'est le tour de cette file de production
								
				// On vérifie si on a les ressources nécessaires en input
				float maxInputRatio = INT32_MAX; // Pourcentage du cycle de production pouvant être réalisé avec des ressources disponibles en input
				for (const auto& inputPair : cycle.getResourceInputs()) {
					Resource resource = inputPair.first;
					float possibleProductions = inputPair.second;
					if (possibleProductions > LogicManager::getInstance().getTown()->getResource(resource)) {
						// Déficit de ressources, on limite la production
						possibleProductions = LogicManager::getInstance().getTown()->getResource(resource) / possibleProductions;
					}
					if(possibleProductions < maxInputRatio) {
						maxInputRatio = possibleProductions;
					}
				}

				// On fait les cycles de production avec ressources en input
				if (maxInputRatio > 0) {
					// Inputs
					for (const auto& inputPair : cycle.getResourceInputs()) {
						Resource resource = inputPair.first;
						int32 quantity = inputPair.second;
						// Ressources internes à la famille
						int32 available = family->getResource(resource);
						if (available > quantity * maxInputRatio) {
							// La famille a assez de ressources, on les prend directement
							family->addResource(resource, quantity * maxInputRatio);
						}
						else {
							// La famille n'a pas assez de ressources, on prend ce qu'elle a et on complète avec la ville
							family->addResource(resource, available);
							LogicManager::getInstance().getTown()->takeResource(resource, (quantity * maxInputRatio) - available, *family);
						}
					}
					// Outputs
					for (const auto& outputPair : cycle.getResourceOutputs()) {
						Resource resource = outputPair.first;
						int32 quantity = outputPair.second;
						// On ajoute les ressources produites à la famille
						family->addResource(resource, quantity * maxInputRatio);
					}
				}
				// Cycles de production avec pénurie de ressources en input
				if (maxInputRatio < 1) {
					float shortageRatio = 1 - maxInputRatio;
					// Outputs
					for (const auto& outputPair : cycle.getResourceOutputs()) {
						Resource resource = outputPair.first;
						int32 quantity = outputPair.second;
						// On ajoute les ressources produites à la famille avec une efficacité de 50% dûe à la pénurie
						family->addResource(resource, quantity * shortageRatio / 2);
						// TODO: augmenter le coût d'entretien à cause de la pénurie
					}
				}
			}
		}
	}

	void Building::logicTick_service() {
		// TEST: on met à jour les maisons servies à chaque tick. Pas optimisé, à améliorer : update quand un bâtiment ou une maison est construite (TODO) ou détruite (DONE) à proximité
		//if(mustUpdateHousesServed)
			this->updateServed();
		mustUpdateServed = false;

		// Décompte des populations servies
		// TODO : consommation de ressources par les populations servies
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

			// Coût total en or du bâtiment
			int32 goldCost = type.getGoldMaintenanceCost();
			// Coût en ressource du bâtiment
			std::map<Resource, int32> resourceCosts = {};
			float resourceShortageRatio = 0;
			// Gain d'or et de prestige grâce aux pops servies
			int32 goldGain = 0;
			int32 prestigeGain = 0;

			for (const auto& pair : totalPopsServed) {
				Pop pop = pair.first;
				int32 popCount = pair.second;
				goldCost += popCount * type.getGoldCostPerPopulation(pop);
				goldGain += popCount * type.getGoldGainPerPopulation(pop);
				prestigeGain += popCount * type.getPrestigeGainPerPopulation(pop);

				// Coûts en ressources
				for (const auto& pairResourceQuantity : type.getResourcesCostPerPopulation(pop)) {
					Resource resource = pairResourceQuantity.first;
					int32 quantity = pairResourceQuantity.second * popCount;
					if (resourceCosts.find(resource) != resourceCosts.end()) {
						resourceCosts[resource] += quantity;
					}
					else {
						resourceCosts[resource] = quantity;
					}
				}
			}

			// On retire les ressources à la famille (et à la ville si besoin) et considérons les éventuelles pénuries
			for (const auto& pair : resourceCosts) {
				Resource resource = pair.first;
				int32 quantity = pair.second;
				// Ressources internes à la famille
				int32 availableInFamily = family->getResource(resource);
				// La famille a-t-elle assez de ressources ?
				if (availableInFamily >= quantity) {
					// La famille a assez de ressources, on les prend directement
					family->addResource(resource, -quantity);
				}
				else {
					// La famille n'a pas assez de ressources, on prend ce qu'elle a...
					family->addResource(resource, -availableInFamily);
					// ... et on complète avec la ville
					int32 quantityLeft = quantity - availableInFamily;
					int32 availableInTown = LogicManager::getInstance().getTown()->getResource(resource);
					if (availableInTown >= quantityLeft) {
						// La ville a assez de ressources, on les prend directement
						LogicManager::getInstance().getTown()->takeResource(resource, quantityLeft, *family);
					}
					else {
						// La ville n'a pas assez de ressources, on prend ce qu'elle a et on déclare une pénurie
						LogicManager::getInstance().getTown()->takeResource(resource, availableInTown, *family);
						quantityLeft -= availableInTown;
						float thisShortage = quantityLeft / quantity;
						if (thisShortage > resourceShortageRatio) {
							resourceShortageRatio = thisShortage;
						}
					}
				}
			}
			// Effets de l'éventuelle pénurie de ressources
			if (resourceShortageRatio > 0) {
				// On réduit les gains d'or et de prestige en fonction de la pénurie : efficacité réduite à 50% de la pénurie
				goldGain = goldGain * (1 - resourceShortageRatio / 2); 
				prestigeGain = prestigeGain * (1 - resourceShortageRatio / 2);
			}

			// Maintenance du bâtiment
			family->removeGold(goldCost);

			// On ajoute l'or et le prestige à la famille
			family->addGold(goldGain);
			family->addPrestige(prestigeGain);
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