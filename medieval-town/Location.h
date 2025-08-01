#pragma once

namespace Models
{
	class Location
	{
	public:
		Location(int x, int y)
			: x(x), y(y) {}
		int getX() const { return x; }
		int getY() const { return y; }

	protected:
		int x; // Coordonnée X de la position
		int y; // Coordonnée Y de la position
	};
}

