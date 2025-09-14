#include "Location.h"
#include <cmath> // Pour std::sqrt

namespace Models
{
	Location::Location(float x, float y, float rotation) : x(x), y(y), rotation(rotation) {}
	float Location::getX() const {
		return this->x;
	}
	float Location::getY() const {
		return this->y;
	}
	float Location::getRotation() const {
		return this->rotation;
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

	// Comparateur d'égalité entre deux Locations pour std::find et std::remove
	bool operator== (Location const& lhs, Location const& rhs) {
		return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
	}
}
