#include "Location.h"
#include <cmath> // Pour std::sqrt

namespace Models
{
	Location::Location(float x, float y, float rotation)
	{
		this->x = x;
		this->y = y;
		this->rotation = rotation;
		// Taille par défaut
		this->sizeX = 1; 
		this->sizeY = 1;
	}
	Location::Location(float x, float y, float rotation, float sizeX, float sizeY)
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
	float Location::maxSizeX = 1;
	float Location::maxSizeY = 1;


	// Getters
	float Location::getX() const {
		return this->x;
	}
	float Location::getY() const {
		return this->y;
	}
	float Location::getRotation() const {
		return this->rotation;
	}
	float Location::getSizeX() const {
		return this->sizeX;
	}
	float Location::getSizeY() const {
		return this->sizeY;
	}

	float Location::getMaxSizeX() {
		return Location::maxSizeX;
	}
	float Location::getMaxSizeY() {
		return Location::maxSizeY;
	}

	float Location::getDistance(const Location& other) const {
		float dx = this->x - other.x;
		float dy = this->y - other.y;
		return std::sqrt(dx * dx + dy * dy); // Vive Pythagore !
	}
	float Location::getDistance(float x, float y) const {
		float dx = this->x - x;
		float dy = this->y - y;
		return std::sqrt(dx * dx + dy * dy);
	}

	bool Location::collisionWith(const Location& other) const {
		// AABB collision detection
		return 
			(std::abs(this->x - other.x) * 2 < (this->getSizeX() + other.getSizeX())) 
			&&
			(std::abs(this->y - other.y) * 2 < (this->getSizeY() + other.getSizeY()));
	}

	// Comparateur d'égalité entre deux Locations pour std::find et std::remove : deux Locations sont égales si elles ont les mêmes coordonnées et la même taille
	static bool operator== (Location const& lhs, Location const& rhs) {
		return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getSizeX() == rhs.getSizeX() && lhs.getSizeY() == rhs.getSizeY();
	}
}
