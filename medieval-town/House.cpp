#include "House.h"
#include "LogicManager.h"
#include "Town.h"

namespace Models
{
	House::House(int32 x, int32 y, int32 rotation, int32 sizeX, int32 sizeY, int32 level, std::map<Pop, int32> startingPops)
		: Location(x, y, rotation, sizeX, sizeY), level(level), pops(startingPops), ServiceReceiver()
	{ 
		// On initialise la date de création à la date actuelle de la ville
		dateCreation = LogicManager::getInstance().getTown()->getDate();

		// Calcul du nombre maximum d'habitants
		updateMaxPops();
	}

	int32 House::getLevel() const
	{
		return level;
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
		// La maison est en cours d'amélioration ?
		if (upgradeInProgress) {
			upgradeDaysDone++;
			// L'amélioration est-elle terminée ?
			if (upgradeDaysDone >= upgradeTime) {
				// On finalise l'amélioration
				upgradeInProgress = false;
				level++;
				upgradePressure = 0; // On réinitialise la pression d'évolution
				updateMaxPops(); // On met à jour les capacités d'accueil
				updateAttractiveness(); // On met à jour l'attractivité
				// Log
				LogicManager::getInstance().log("La maison en " + std::to_string(getX()) + "," + std::to_string(getY()) + " a évolué au niveau " + std::to_string(level));
			}
		}

		// La maison peut-elle évoluer ?
		if (canUpgrade()) {
			upgradePressure++;
			// Chaque point de pression donne 10% de chances d'évolution par jour
			if (LogicManager::getInstance().randRange(1, 10) <= upgradePressure) {
				// On lance l'amélioration
				upgradeInProgress = true;
				upgradeDateStart = LogicManager::getInstance().getTown()->getDate();
				upgradeTime = 5; // TODO: définir la durée en fonction du niveau et de la taille
				upgradeDaysDone = 0;
				LogicManager::getInstance().log("La maison en " + std::to_string(getX()) + "," + std::to_string(getY()) + " commence à évoluer");
			}
		}
	}

	void House::addPop(Pop pop, int32 number)
	{
		pops[pop] += number;
	}

	int32 House::getBaseCapacity(int32 sizeX, int32 sizeY)
	{
		return sizeX * (sizeY - 1) / 4; // Capacité de base : 1 pop par 4 mètres carrés (-1 sur l'axe Y car il y a la porte)
	}

	bool House::canUpgrade() const
	{
		// Une maison peut être améliorée si :
		// - Elle n'est pas déjà en cours d'amélioration
		// - Elle n'a pas atteint le niveau maximum (9)
		// - Elle a atteint son maximum d'habitants pour la strate la plus élevée de population qu'elle peut accueillir
		// - Elle offre une satisfaction de service suffisante pour la strate la plus élevée de population qu'elle peut accueillir

		// Aucune upgrade en cours
		if (upgradeInProgress) {
			return false;
		}

		// Pas encore au niveau maximum
		if (level >= 9) {
			return false;
		}

		// On identifie la strate de population la plus élevée pouvant être accueillie : niveaux 1-3 : Gueux, 4-6 : Bourgeois, 7-9 : Nobles
		Pop highestPop;
		if (level >= 7) {
			highestPop = Pop::Noble;
		}
		else if (level >= 4) {
			highestPop = Pop::Bourgeois;
		}
		else {
			highestPop = Pop::Gueux;
		}

		if(getFreePop(highestPop) > 0) {
			// La maison n'est pas pleine pour cette strate de population
			return false;
		}

		// Au niveau 1/4/7, on demande -2 d'attractivité, au niveau 2/5/8 -1, au niveau 3/6 0
		int32 requiredAttractiveness;
		if(level == 1 || level == 4 || level == 7) {
			requiredAttractiveness = -2;
		}
		else if(level == 2 || level == 5 || level == 8) {
			requiredAttractiveness = -1;
		}
		else {
			requiredAttractiveness = 0;
		}
		if (getAttractiveness(highestPop) < requiredAttractiveness) {
			return false;
		}

		// On a passé toutes les vérifications : la maison est digne d'évoluer
		return true;
	}

	void House::updateMaxPops()
	{
		// Capacité de base en fonction de la taille
		int32 baseCapacity = House::getBaseCapacity(getSizeX(), getSizeY());
		// On calcule les capacités maximales en fonction du niveau
		switch (level) {
			case 1:
				maxPops[Pop::Gueux] = baseCapacity;
				maxPops[Pop::Bourgeois] = 0;
				maxPops[Pop::Noble] = 0;
				break;
			case 2:
				maxPops[Pop::Gueux] = baseCapacity * 2;
				maxPops[Pop::Bourgeois] = 0;
				maxPops[Pop::Noble] = 0;
				break;
			case 3:
				maxPops[Pop::Gueux] = baseCapacity * 3;
				maxPops[Pop::Bourgeois] = 0;
				maxPops[Pop::Noble] = 0;
				break;
			case 4:
				maxPops[Pop::Gueux] = baseCapacity * 3;
				maxPops[Pop::Bourgeois] = baseCapacity;
				maxPops[Pop::Noble] = 0;
				break;
			case 5:
				maxPops[Pop::Gueux] = baseCapacity * 3;
				maxPops[Pop::Bourgeois] = baseCapacity * 2;
				maxPops[Pop::Noble] = 0;
				break;
			case 6:
				maxPops[Pop::Gueux] = baseCapacity * 3;
				maxPops[Pop::Bourgeois] = baseCapacity * 3;
				maxPops[Pop::Noble] = 0;
				break;
			case 7:
				maxPops[Pop::Gueux] = baseCapacity * 3;
				maxPops[Pop::Bourgeois] = baseCapacity * 3;
				maxPops[Pop::Noble] = baseCapacity;
				break;
			case 8:
				maxPops[Pop::Gueux] = baseCapacity * 3;
				maxPops[Pop::Bourgeois] = baseCapacity * 3;
				maxPops[Pop::Noble] = baseCapacity * 2;
				break;
			case 9:
				maxPops[Pop::Gueux] = baseCapacity * 3;
				maxPops[Pop::Bourgeois] = baseCapacity * 3;
				maxPops[Pop::Noble] = baseCapacity * 3;
				break;
			default:
				break;
		}
	}
}
