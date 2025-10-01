#pragma once

namespace Models
{
	// Elément positionné dans la ville
	class Location
	{
	public:
		// Location avec une taille par défaut de 1x1 (un tile)
		Location(float x, float y, float rotation);
		// Location avec une taille spécifiée
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

		// Détection de collision entre deux Locations en "axis-aligned bounding boxes" (AABB). TODO: prendre en compte la rotation
		bool collisionWith(const Location& other) const;

		// Possède un operator==

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

