#pragma once
#include <map>
#include <vector>
#include "Service.h"
#include "Pop.h"
#include <cstdint>
using int32 = int32_t; // Match le type "int" d'Unreal Engine

namespace Models
{
	// Forward declarations
	class Building;


	// Classe de base pour les entités pouvant recevoir des services : maisons, tuiles...
	class ServiceReceiver
	{
	public:
		ServiceReceiver();

		static const std::map<Pop, std::vector<Service>> popServices; // Services requis par chaque type de population

		Building* getServiceBuilding(Service service) const; // Retourne le bâtiment de service desservant cet endroit pour le service donné ; nullptr si pas de bâtiment
		std::map<Service, Building*> getAllServiceBuildings() const; // Retourne la liste des bâtiments de service desservant cet endroit

		void addService(Service service, Building* building); // Ajoute un bâtiment de service desservant cet endroit
		void removeService(Service service); // Retire le bâtiment de service desservant cet endroit pour le service donné

		void addMarginalService(Service service, Building* building); // Ajoute un bâtiment de service pouvant desservir cet endroit pour un nouvel habitant
		void removeMarginalService(Service service, Building* building); // Retire le bâtiment de service pouvant desservir cet endroit pour le service donné pour un nouvel habitant

		int32 getAttractiveness(Pop pop) const; // Retourne l'attractivité pour une population en fonction des services disponibles : 0 signifie que tous les services requis sont disponibles, et chaque service indisponible réduit l'attractivité de 1

		static int32 getNumberOfServicesForPop(Pop pop); // Retourne le nombre de services requis pour une population donnée

	protected:
		virtual void updateAttractiveness(); // Met à jour l'attractivité après que les services disponibles aient évolués (virtual pour laisser Tile l'override)

	private:
		std::map<Service, Building*> serviceBuildings; // Bâtiments de service desservant cet endroit

		std::map<Service, std::vector<Building*>> marginalServiceBuildings; // Pour chaque service, liste des bâtiments de service à portée pouvant accueillir un habitant de plus, afin de calculer l'attractivité. Privée car toute modification doit passer par les setters afin que soit appelé updateAttractiveness()

		std::map<Pop, int32> attractiveness; // Attractivité pour une population en fonction des services disponibles
	};
}

