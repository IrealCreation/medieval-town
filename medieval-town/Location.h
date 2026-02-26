#pragma once
#include <cstdint>
#include <string>
using int32 = int32_t; // Match le type "int" d'Unreal Engine

namespace Models
{
	// Elément positionné dans la ville
	class Location
	{
	public:
		// Location avec une taille par défaut de 1x1 (un tile)
		Location(int32 x, int32 y, float rotation);
		// Location avec une taille spécifiée
		Location(int32 x, int32 y, float rotation, int32 sizeX, int32 sizeY);

		int32 getX() const;
		int32 getY() const;
		float getRotation() const;
		int32 getSizeX() const;
		int32 getSizeY() const;

		std::string getId() const;

		static int32 getMaxSizeX();
		static int32 getMaxSizeY();

		float getDistance(const Location& other) const;
		float getDistance(int32 otherX, int32 otherY) const;

		// Détection de collision entre deux Locations en "axis-aligned bounding boxes" (AABB). TODO: prendre en compte la rotation
		bool collisionWith(const Location& other) const;

		// Possède un operator==

		~Location(); // Destructeur

	protected:
		int32 x;
		int32 y;
		float rotation;
		int32 sizeX; // Taille totale sur l'axe X
		int32 sizeY; // Taille totale sur l'axe Y

		std::string id; // ID généré à la création sur le modèle : [Type]_[X]_[Y]_[dateCreation]
		virtual void setId(); // Génère l'ID à partir du type et de la date de création, puis ajoute cette Location à la map du LogicManager

		static int32 maxSizeX; // Taille maximale sur l'axe X parmi toutes les Locations
		static int32 maxSizeY; // Taille maximale sur l'axe Y parmi toutes les Locations
	};
}

