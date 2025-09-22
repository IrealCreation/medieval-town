#include "Location.h"
#include <cmath> // Pour std::sqrt

namespace Models
{
	Location::Location(float x, float y, float rotation)
	{
		this->x = x;
		this->y = y;
		this->rotation = rotation;
		// Taille par d�faut
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
	}


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

	// Comparateur d'�galit� entre deux Locations pour std::find et std::remove : deux Locations sont �gales si elles ont les m�mes coordonn�es et la m�me taille
	static bool operator== (Location const& lhs, Location const& rhs) {
		return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getSizeX() == rhs.getSizeX() && lhs.getSizeY() == rhs.getSizeY();
	}
}
