#include "House.h"
#include "LogicManager.h"
#include "Town.h"

namespace Models
{
	House::House(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 niveau)
		: Location(x, y, rotation, sizeX, sizeY), niveau(niveau)
	{ 
		// On initialise la date de création à la date actuelle de la ville
		dateCreation = LogicManager::getInstance().getTown()->getDate();

		// Initialisation de la map des pops résidentes
		pops = {
			{ Pop::Gueux, 2 },
			{ Pop::Bourgeois, 0 },
			{ Pop::Noble, 0 }
		};
		// TODO: ajuster les pops en fonction du niveau de la maison
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
	void House::logicTick()
	{
		// TODO: gérer les pops résidentes, leurs besoins, leur croissance...
	}
}
