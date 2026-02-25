#include "Location.h"
#include "LogicManager.h"
#include <cmath> // Pour std::sqrt
#include <wtypes.h>

namespace Models
{
	Location::Location(int32 x, int32 y, float rotation)
	{
		this->x = x;
		this->y = y;
		this->rotation = rotation;
		// Taille par défaut
		this->sizeX = 1; 
		this->sizeY = 1;
	}
	Location::Location(int32 x, int32 y, float rotation, int32 sizeX, int32 sizeY)
	{
		this->x = x;
		this->y = y;
		this->rotation = rotation;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		// Mise à jour des tailles maximales si nécessaire
		if (sizeX > Location::maxSizeX)
			Location::maxSizeX = sizeX;
		if (sizeY > Location::maxSizeY)
			Location::maxSizeY = sizeY;
	}
	
	// Initialisation des attributs statiques
	int32 Location::maxSizeX = 1;
	int32 Location::maxSizeY = 1;


	// Getters
	int32 Location::getX() const {
		return this->x;
	}
	int32 Location::getY() const {
		return this->y;
	}
	float Location::getRotation() const {
		return this->rotation;
	}
	int32 Location::getSizeX() const {
		return this->sizeX;
	}
	int32 Location::getSizeY() const {
		return this->sizeY;
	}

	std::string Location::getId() const {
		return this->id;
	}

	int32 Location::getMaxSizeX() {
		return Location::maxSizeX;
	}
	int32 Location::getMaxSizeY() {
		return Location::maxSizeY;
	}

	float Location::getDistance(const Location& other) const {
		return getDistance(other.x, other.y);
	}
	float Location::getDistance(int32 otherX, int32 otherY) const {
		int32 dx = this->x - otherX;
		int32 dy = this->y - otherY;
		return std::sqrt(dx * dx + dy * dy);
	}

	bool Location::collisionWith(const Location& other) const {
		// AABB collision detection
		return 
			(std::abs(static_cast<int>(this->x - other.x) * 2)
				< this->getSizeX() + other.getSizeX())
			&&
			(std::abs(static_cast<int>(this->y - other.y) * 2) < this->getSizeY() + other.getSizeY());
	}

	// Comparateur d'égalité entre deux Locations pour std::find et std::remove : deux Locations sont égales si elles ont les mêmes coordonnées et la même taille
	static bool operator== (Location const& lhs, Location const& rhs) {
		return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getSizeX() == rhs.getSizeX() && lhs.getSizeY() == rhs.getSizeY();
	}

	void Location::setId(std::string type, int32 dateCreation) {
		// Génération de l'ID : [Type]_[X]_[Y]_[dateCreation]
		this->id = type + "_" + std::to_string(this->x) + "_" + std::to_string(this->y) + "_" + std::to_string(dateCreation);

		// On ajoute cette Location à la map du LogicManager
		LogicManager::getInstance().addIdLocation(this);
	}
}
