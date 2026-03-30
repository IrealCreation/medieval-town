#include "Geometry.h"
#include <iostream>
#include <string>
#include <cmath>

namespace Geometry {
	float Segment::Length() const {
		float dx = p2.x - p1.x;
		float dy = p2.y - p1.y;
		return std::sqrt(dx * dx + dy * dy);
	}

	float Triangle::Area() const {
		float a = AB.Length();
		float b = BC.Length();
		float c = CA.Length();
		float s = (a + b + c) / 2.0f;
		return std::sqrt(s * (s - a) * (s - b) * (s - c));
	}

	float Quad::Area() const {
		return ABC.Area() + ACD.Area();
	}

	float WhichSide(const Point& p1, const Point& p2, const Point& p3) {
		return (p1.x - p3.x) * (p2.y - p3.y)
			- (p2.x - p3.x) * (p1.y - p3.y);
	}

	bool IsPointInTriangle(const Point& P, const Triangle& T) {
		const float EPS = 1e-6f; // Used to avoid issues where a float is unprecise and values "almost" 0 instead of 0

		float side1 = WhichSide(P, T.A, T.B);
		float side2 = WhichSide(P, T.B, T.C);
		float side3 = WhichSide(P, T.C, T.A);


		bool hasNegative =
			(side1 < -EPS) || (side2 < -EPS) || (side3 < -EPS);

		bool hasPositive =
			(side1 > EPS) || (side2 > EPS) || (side3 > EPS);

		return !(hasNegative && hasPositive);
	}

	bool IsPointInQuad(const Point& P, const Quad& Q) {
		return  IsPointInTriangle(P, Q.ABC) ||
			IsPointInTriangle(P, Q.ACD);
	}
}