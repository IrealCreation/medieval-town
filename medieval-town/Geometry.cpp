#include "Geometry.h"
#include <cmath>
#include <vector>

namespace Geometry {
	float Segment::length() const {
		float dx = p2.x - p1.x;
		float dy = p2.y - p1.y;
		return std::sqrt(dx * dx + dy * dy);
	}

	float Triangle::area() const {
		float a = AB.length();
		float b = BC.length();
		float c = CA.length();
		float s = (a + b + c) / 2.0f;
		return std::sqrt(s * (s - a) * (s - b) * (s - c));
	}

	float Quad::area() const {
		return ABC.area() + ACD.area();
	}

	string Quad::toString() const {
		return "Quad(" + std::to_string(A.x) + "," + std::to_string(A.y) + " ; "
			+ std::to_string(B.x) + "," + std::to_string(B.y) + " ; "
			+ std::to_string(C.x) + "," + std::to_string(C.y) + " ; "
			+ std::to_string(D.x) + "," + std::to_string(D.y) + ")";
	}

	float whichSide(const Point& p1, const Point& p2, const Point& p3) {
		return (p1.x - p3.x) * (p2.y - p3.y)
			- (p2.x - p3.x) * (p1.y - p3.y);
	}

	bool isPointInTriangle(const Point& P, const Triangle& T) {
		const float EPS = 1e-6f; // Used to avoid issues where a float is unprecise and values "almost" 0 instead of 0

		float side1 = whichSide(P, T.A, T.B);
		float side2 = whichSide(P, T.B, T.C);
		float side3 = whichSide(P, T.C, T.A);


		bool hasNegative =
			(side1 < -EPS) || (side2 < -EPS) || (side3 < -EPS);

		bool hasPositive =
			(side1 > EPS) || (side2 > EPS) || (side3 > EPS);

		return !(hasNegative && hasPositive);
	}

	bool isPointInQuad(const Point& P, const Quad& Q) {
		return  isPointInTriangle(P, Q.ABC) ||
			isPointInTriangle(P, Q.ACD);
	}

	Quad createQuad(Point center, float sizeX, float sizeY, float rotationDegrees) {
		std::vector<Point> corners(4);

		// 1. Conversion de l'angle en radians
		float angleRad = rotationDegrees * M_PI / 180.0;

		// 2. Calcul du cosinus et du sinus (une seule fois pour l'optimisation)
		float cosTheta = cos(angleRad);
		float sinTheta = sin(angleRad);

		// 3. Demi-dimensions (distance du centre aux bords)
		float halfWidth = sizeX / 2.0;
		float halfHeight = sizeY / 2.0;

		// 4. Calcul des 4 coins
		// On définit les coins locaux non rotés puis on applique la rotation + translation
		// Formule : 
		// x' = center.x + (x_local * cos - y_local * sin)
		// y' = center.y + (x_local * sin + y_local * cos)

		// Coin 1 : Haut-Gauche (-dx, -dy)
		corners[0].x = center.x + (-halfWidth * cosTheta - (-halfHeight) * sinTheta);
		corners[0].y = center.y + (-halfWidth * sinTheta + (-halfHeight) * cosTheta);

		// Coin 2 : Haut-Droite (dx, -dy)
		corners[1].x = center.x + (halfWidth * cosTheta - (-halfHeight) * sinTheta);
		corners[1].y = center.y + (halfWidth * sinTheta + (-halfHeight) * cosTheta);

		// Coin 3 : Bas-Droite (dx, dy)
		corners[2].x = center.x + (halfWidth * cosTheta - halfHeight * sinTheta);
		corners[2].y = center.y + (halfWidth * sinTheta + halfHeight * cosTheta);

		// Coin 4 : Bas-Gauche (-dx, dy)
		corners[3].x = center.x + (-halfWidth * cosTheta - halfHeight * sinTheta);
		corners[3].y = center.y + (-halfWidth * sinTheta + halfHeight * cosTheta);

		return Quad(corners[0], corners[1], corners[2], corners[3]);
	}

	Quad createQuad(float x, float y, float sizeX, float sizeY, float rotationDegrees) {
		return createQuad(Point{ x, y }, sizeX, sizeY, rotationDegrees);
	}

}