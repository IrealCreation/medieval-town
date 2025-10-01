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

		static float getMaxSizeX();
		static float getMaxSizeY();

		float getDistance(const Location& other) const;
		float getDistance(float x, float y) const;

		// D�tection de collision entre deux Locations en "axis-aligned bounding boxes" (AABB). TODO: prendre en compte la rotation
		bool collisionWith(const Location& other) const;

		// Poss�de un operator==

	protected:
		float x;
		float y;
		float rotation;
		float sizeX; // Taille totale sur l'axe X
		float sizeY; // Taille totale sur l'axe Y

		static float maxSizeX; // Taille maximale sur l'axe X parmi toutes les Locations
		static float maxSizeY; // Taille maximale sur l'axe Y parmi toutes les Locations
	};
}

