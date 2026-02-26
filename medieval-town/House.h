#pragma once
#include "Location.h"
#include <map>
#include "Pop.h"
#include "Service.h"
#include "ServiceReceiver.h" 
#include <cstdint>
using int32 = int32_t; // Match le type "int" d'Unreal Engine

namespace Models
{
    // Forward declarations
	class Building;

    class House : public Location, public ServiceReceiver
    {
    public:
        House(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau, std::map<Pop, int32> startingPops);

        // Getters
        int32 getLevel() const;
        int32 getPop(Pop pop) const; // Retourne le nombre de pops résidentes dans la maison pour le type de pop donné
		int32 getPopTotal() const; // Retourne le nombre total de pops résidentes dans la maison
        int32 getMaxPop(Pop pop) const; // Retourne le nombre maximum d'habitants pour le type de pop donné
		int32 getFreePop(Pop pop) const; // Retourne le nombre de places libres pour le type de pop donné

		void logicTick();

		void addPop(Pop pop, int32 number); // Ajoute des habitants dans la maison

        static const int32 minSizeX = 4; // Taille minimale sur l'axe X d'une maison
        static const int32 minSizeY = 7; // Taille minimale sur l'axe Y d'une maison

		static int32 getBaseCapacity(int32 sizeX, int32 sizeY); // Retourne la capacité de base d'une maison en fonction de sa taille

		bool canUpgrade() const; // La maison peut-elle être améliorée ?

    protected:
		int32 dateCreation = 0; // Date de création de la maison (fin du chantier de construction)
		int32 level = 1; // Niveau de la maison, lui permettant d'accueillir plus de pop et de meilleures pops

		void setId() override;

        std::map<Pop, int32> pops; // Populations résidentes dans la maison
        std::map<Pop, int32> maxPops; // Nombre maximum d'habitants dans la maison

		void updateMaxPops(); // Met à jour le nombre maximum d'habitants en fonction de la taille et du niveau

		bool upgradeInProgress = false; // Indique si une amélioration de la maison est en cours
		int32 upgradePressure = 0; // Pression accumulée pour l'évolution de la maison. Augmente de 1 par jour si canUpgrade() est true. Chaque point donne 10% de chances d'évolution par jour.
		int32 upgradeDateStart = 0; // Date de début de l'amélioration
		int32 upgradeTime = 0; // Durée nécessaire à l'amélioration, en jours
		int32 upgradeDaysDone = 0; // Jours d'amélioration effectués
    };
}

