#pragma once
#include <map>
#include <vector>
#include "Service.h"
#include "Pop.h"

namespace Models
{
	// Forward declarations
	class Building;


	// Classe de base pour les entit�s pouvant recevoir des services : maisons, tuiles...
	class ServiceReceiver
	{
	public:
		ServiceReceiver();

		const std::map<Pop, std::vector<Service>> popServices = {
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

		Building* getServiceBuilding(Service service) const; // Retourne le b�timent de service desservant cet endroit pour le service donn� ; nullptr si pas de b�timent
		std::map<Service, Building*> getAllServiceBuildings() const; // Retourne la liste des b�timents de service desservant cet endroit

		void addService(Service service, Building* building); // Ajoute un b�timent de service desservant cet endroit
		void removeService(Service service); // Retire le b�timent de service desservant cet endroit pour le service donn�

		float getAttractiveness(Pop pop) const; // Retourne l'attractivit� pour une population en fonction des services disponibles

	private:
		std::map<Service, Building*> serviceBuildings; // B�timents de service desservant cet endroit. Port�e priv�e car toute modification doit passer par les setters afin que soit appel� updateAttractiveness()

		std::map<Pop, float> attractiveness; // Attractivit� pour une population en fonction des services disponibles

		void updateAttractiveness(); // Met � jour l'attractivit� apr�s que les services disponibles aient �volu�s
	};
}

