#pragma once

// Include guard pour �viter les inclusions multiples de ce header qui, �tant un parent d'autres classes, doit �tre inclus plusieurs fois
#ifndef MODELS_LOCATION
#define MODELS_LOCATION

namespace Models
{
	// El�ment positionn� dans la ville
	class Location
	{
	public:
		Location(float x, float y, float rotation);

		float getX() const;
		float getY() const;
		float getRotation() const;
		float getDistance(const Location& other) const;

	protected:
		float x;
		float y;
		float rotation;
	};
}

#endif // !MODELS_LOCATION

