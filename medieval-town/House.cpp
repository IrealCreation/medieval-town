#include "House.h"
#include "LogicManager.h"
#include "Town.h"

namespace Models
{
	House::House(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau, std::map<Pop, int32> startingPops)
		: Location(x, y, rotation, sizeX, sizeY), niveau(niveau), pops(startingPops), ServiceReceiver()
	{ 
		// On initialise la date de création à la date actuelle de la ville
		dateCreation = LogicManager::getInstance().getTown()->getDate();

		// Calcul du nombre maximum d'habitants en fonction de la taille
		int32 baseCapacity = House::getBaseCapacity(sizeX, sizeY);
		maxPops = {
			{ Pop::Gueux, baseCapacity },
			{ Pop::Bourgeois, 0 },
			{ Pop::Noble, 0 }
		};
		// TODO: prendre en compte le niveau de la maison
	}
	int32 House::getNiveau() const
	{
		return niveau;
	}
	int32 House::getPop(Pop pop) const
	{
		if (pops.find(pop) != pops.end())
			return pops.at(pop);
		else
			return 0;
	}
	int32 House::getPopTotal() const
	{
		int32 total = 0;
		for (const auto& pair : pops) {
			total += pair.second;
		}
		return total;
	}
	int32 House::getMaxPop(Pop pop) const
	{
		if (maxPops.find(pop) != maxPops.end())
			return maxPops.at(pop);
		else
			return 0;
	}
	int32 House::getFreePop(Pop pop) const
	{
		return getMaxPop(pop) - getPop(pop);
	}

	void House::logicTick()
	{
		// TODO: gérer les pops résidentes, leurs besoins, leur croissance...
	}

	void House::addPop(Pop pop, int32 number)
	{
		pops[pop] += number;
	}

	int32 House::getBaseCapacity(int32 sizeX, int32 sizeY)
	{
		return sizeX * sizeY / 4; // Capacité de base : 1 pop par 4 mètres carrés
	}
}
