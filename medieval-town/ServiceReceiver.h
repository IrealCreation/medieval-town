#pragma once
#include <map>
#include "Service.h"

namespace Models
{
	// Forward declarations
	class Building;


	// Classe de base pour les entités pouvant recevoir des services : maisons, tuiles...
	class ServiceReceiver
	{
	public:
		ServiceReceiver();

		Building* getServiceBuilding(Service service) const; // Retourne le bâtiment de service desservant cet endroit pour le service donné ; nullptr si pas de bâtiment
		std::map<Service, Building*> getAllServiceBuildings() const; // Retourne la liste des bâtiments de service desservant cet endroit

		void addService(Service service, Building* building); // Ajoute un bâtiment de service desservant cet endroit
		void removeService(Service service); // Retire le bâtiment de service desservant cet endroit pour le service donné

		// TODO: attractivité

	protected:
		std::map<Service, Building*> serviceBuildings; // Bâtiments de service desservant cet endroit
	};
}

