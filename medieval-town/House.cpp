#include "House.h"
#include "LogicManager.h"
#include "Town.h"

namespace Models
{
	House::House(int x, int y, int rotation, int sizeX, int sizeY, int niveau)
		: Location(x, y, rotation), sizeX(sizeX), sizeY(sizeY), niveau(niveau)
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
	int House::getSizeX() const
	{
		return sizeX;
	}
	int House::getSizeY() const
	{
		return sizeY;
	}
	int House::getNiveau() const
	{
		return niveau;
	}
	int House::getPop(Pop pop) const
	{
		if (pops.find(pop) != pops.end())
			return pops.at(pop);
		else
			return 0;
	}
	int House::getPopTotal() const
	{
		int total = 0;
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
