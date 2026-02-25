#include "ServiceReceiver.h"
#include "Building.h"
#include "LogicManager.h"
#include <algorithm>
using std::map;
using std::find;


namespace Models
{
	ServiceReceiver::ServiceReceiver() 
	{
		// Attractivité à 0 - nombre de services requis par défaut
		attractiveness = {
			{ Pop::Gueux, 0 - getNumberOfServicesForPop(Pop::Gueux) },
			{ Pop::Bourgeois, 0 - getNumberOfServicesForPop(Pop::Bourgeois) },
			{ Pop::Noble, 0 - getNumberOfServicesForPop(Pop::Noble) }
		};
	}

	// Définition de la map statique des services requis par chaque pop
	const std::map<Pop, std::vector<Service>> ServiceReceiver::popServices = {
		{
			Pop::Gueux,
			{ Service::Priere, Service::Eau, Service::Garde, Service::Social, Service::Picole }
		},
		{
			Pop::Bourgeois,
			{ Service::Priere, Service::Monachisme, Service::Eau, Service::Linge, Service::Soin, Service::Garde, Service::Chatiment, Service::Social, Service::Diner, Service::Comedie }
		},
		{
			Pop::Noble,
			{ Service::Priere, Service::Monachisme, Service::Etude, Service::Eau, Service::Linge, Service::Soin, Service::Bain, Service::Garde, Service::Chatiment, Service::Justice, Service::Social, Service::Diner, Service::Comedie, Service::Art, Service::Plaisir }
		}
	};

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

	int32 ServiceReceiver::getAttractiveness(Pop pop) const
	{
		if (attractiveness.find(pop) == attractiveness.end()) {
			LogicManager::getInstance().log("ServiceReceiver::getAttractiveness : Pop " + std::to_string(static_cast<int>(pop)) + " not found");
			return -999;
		}
		return attractiveness.find(pop)->second;
	}

	void ServiceReceiver::updateAttractiveness()
	{
		// Les scores initiaux de chaque pop sont 0 moins le nombre de services requis pour cette pop
		map<Pop, int32> scoreByPop = {
			{ Pop::Gueux, 0 - getNumberOfServicesForPop(Pop::Gueux) },
			{ Pop::Bourgeois, 0 - getNumberOfServicesForPop(Pop::Bourgeois) },
			{ Pop::Noble, 0 - getNumberOfServicesForPop(Pop::Noble) }
		};

		if (marginalServiceBuildings.empty()) {
			// Il n'y a aucun bâtiment de service qui nous dessert
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

		// Déprécié : on garde juste le nombre de services disponibles pour chaque pop plutôt que de faire une moyenne
		// On divise le score d'attractivité pour chaque pop par la quantité de services que cette pop requiert
		/* for (auto& pop_score : scoreByPop)
		{
			// Pas besoin de diviser si le score est à 0
			if (pop_score.second == 0.0f)
				continue;

			auto it = popServices.find(pop_score.first);
			pop_score.second /= static_cast<float>(it->second.size());
		}*/

		// On attribue les nouveaux score d'attractivité
		attractiveness = scoreByPop;
	}

	int32 ServiceReceiver::getNumberOfServicesForPop(Pop pop)
	{
		// TODO: peut-être utiliser plutôt un cache statique pour éviter de faire un size() à chaque appel ?
		return static_cast<int32>(popServices.find(pop)->second.size());
	}

}
