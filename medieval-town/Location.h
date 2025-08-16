#pragma once

namespace Models
{
	// Elément positionné dans la ville
	class Location
	{
	public:
		Location(float x, float y);

		float getX() const;
		float getY() const;
		float getDistance(const Location& other) const;

	protected:
		float x;
		float y;
	};
}

