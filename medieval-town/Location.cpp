#include "Location.h"
#include <cmath> // Pour std::sqrt

namespace Models
{
	Location::Location(float x, float y) : x(x), y(y) {}
	float Location::getX() const {
		return x;
	}
	float Location::getY() const {
		return y;
	}
	float Location::getDistance(const Location& other) const {
		float dx = x - other.x;
		float dy = y - other.y;
		return std::sqrt(dx * dx + dy * dy); // Vive Pythagore !
	}

	// Comparateur d'égalité entre deux Locations pour std::find et std::remove
	bool operator== (Location const& lhs, Location const& rhs) {
		return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
	}
}
