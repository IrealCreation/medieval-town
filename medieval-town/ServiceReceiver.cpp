#include "ServiceReceiver.h"
#include "Building.h"
#include <algorithm>
using std::map;
using std::find;


namespace Models
{
	ServiceReceiver::ServiceReceiver() 
	{
		// Attractivité à 0 par défaut
		attractiveness = {
			{ Pop::Gueux, 0.0f },
			{ Pop::Bourgeois, 0.0f },
			{ Pop::Noble, 0.0f }
		};
	}

	Building* ServiceReceiver::getServiceBuilding(Service service) const
	{
		if (serviceBuildings.find(service) != serviceBuildings.end())
			return serviceBuildings.at(service);
		else
			return nullptr;
	}
	std::map<Service, Building*> ServiceReceiver::getAllServiceBuildings() const
	{
		return serviceBuildings;
	}

	void ServiceReceiver::addService(Service service, Building* building)
	{
		serviceBuildings[service] = building;
	}
	void ServiceReceiver::removeService(Service service)
	{
		serviceBuildings.erase(service);
	}

	void ServiceReceiver::addMarginalService(Service service, Building* building)
	{
		marginalServiceBuildings[service].push_back(building);
		this->updateAttractiveness();
	}
	void ServiceReceiver::removeMarginalService(Service service, Building* building)
	{
		// On retire le bâtiment de la liste des bâtiments marginaux pour ce service
		auto& buildings = marginalServiceBuildings[service];
		auto it = find(buildings.begin(), buildings.end(), building);
		if (it != buildings.end()) {
			buildings.erase(it);
		}

		// S'il n'y a plus de bâtiment pour ce service, on retire l'entrée de la map et on met à jour l'attractivité
		if (buildings.empty()) {
			marginalServiceBuildings.erase(service);
			this->updateAttractiveness();
		}
	}

	float ServiceReceiver::getAttractiveness(Pop pop) const
	{
		return attractiveness.find(pop)->second;
	}

	void ServiceReceiver::updateAttractiveness()
	{
		map<Pop, float> scoreByPop = {
			{ Pop::Gueux, 0.0f },
			{ Pop::Bourgeois, 0.0f },
			{ Pop::Noble, 0.0f }
		};

		if (serviceBuildings.empty()) {
			// Il n'y a aucun bâtiment de service qui nous dessert : l'attractivité est de 0
			attractiveness = scoreByPop;
			return;
		}

		// On parcourt tous les services marginaux disponibles
		for(const auto& service_building : marginalServiceBuildings)
		{
			// Pour chaque service desservi, on regarde chaque pop afin de vérifier si elle désire ce service
			for (const auto& pop_services : popServices)
			{
				// Est-ce que le service de ce bâtiment est présent dans la liste de services de cette population ?
				if (find(pop_services.second.begin(), pop_services.second.end(), service_building.first) != pop_services.second.end()) 
				{
					// Si oui, on accroit le score d'attractivité pour cette pop de 1
					scoreByPop[pop_services.first]++;
				}
			}
		}

		// On divise le score d'attractivité pour chaque pop par la quantité de services que cette pop requiert
		for(auto& pop_score : scoreByPop) 
		{
			// Pas besoin de diviser si le score est à 0
			if (pop_score.second == 0.0f)
				continue;

			auto it = popServices.find(pop_score.first);
			pop_score.second /= static_cast<float>(it->second.size());
		}

		// On attribue les nouveaux score d'attractivité
		attractiveness = scoreByPop;
	}

}
