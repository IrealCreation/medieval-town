#pragma once

namespace Models
{
	// El�ment positionn� dans la ville
	class Location
	{
	public:
		Location(float x, float y);

		float getX() const;
		float getY() const;
		float getDistance(const Location& other) const;

	private:
		float x;
		float y;
	};
}

