#pragma once

namespace Models
{
	// Elément positionné dans la ville
	class Location
	{
	public:
		Location(float x, float y, float rotation);

		float getX() const;
		float getY() const;
		float getRotation() const;
		float getDistance(const Location& other) const;
		float getDistance(float x, float y) const;

	protected:
		float x;
		float y;
		float rotation;
	};
}

