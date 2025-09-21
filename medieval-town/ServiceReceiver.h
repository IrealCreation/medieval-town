#pragma once
#include <map>
#include "Service.h"

namespace Models
{
	// Forward declarations
	class Building;


	// Classe de base pour les entit�s pouvant recevoir des services : maisons, tuiles...
	class ServiceReceiver
	{
	public:
		ServiceReceiver();

		Building* getServiceBuilding(Service service) const; // Retourne le b�timent de service desservant cet endroit pour le service donn� ; nullptr si pas de b�timent
		std::map<Service, Building*> getAllServiceBuildings() const; // Retourne la liste des b�timents de service desservant cet endroit

		void addService(Service service, Building* building); // Ajoute un b�timent de service desservant cet endroit
		void removeService(Service service); // Retire le b�timent de service desservant cet endroit pour le service donn�

		// TODO: attractivit�

	protected:
		std::map<Service, Building*> serviceBuildings; // B�timents de service desservant cet endroit
	};
}

