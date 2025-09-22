#pragma once

namespace Models
{
	// El�ment positionn� dans la ville
	class Location
	{
	public:
		// Location avec une taille par d�faut de 1x1 (un tile)
		Location(float x, float y, float rotation);
		// Location avec une taille sp�cifi�e
		Location(float x, float y, float rotation, float sizeX, float sizeY);

		float getX() const;
		float getY() const;
		float getRotation() const;
		float getSizeX() const;
		float getSizeY() const;

		float getDistance(const Location& other) const;
		float getDistance(float x, float y) const;

	protected:
		float x;
		float y;
		float rotation;
		float sizeX; // Taille totale sur l'axe X
		float sizeY; // Taille totale sur l'axe Y
	};
}

