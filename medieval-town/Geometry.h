#pragma once
#include <string>
using std::string;
using int32 = int32_t; // Match le type "int" d'Unreal Engine

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

///// Let's do some geometry! /////
namespace Geometry {

    // Point in spaaaaace.
    struct Point {

		Point() : x(0), y(0) {}
		Point(float x, float y) : x(x), y(y) {}

        float x = 0.0f;
        float y = 0.0f;
    };

    // Line between two points.
    struct Segment {
        Point p1;
        Point p2;

        float length() const;
    };

    // Basic triangle.
    struct Triangle {

        Triangle(Point A, Point B, Point C);

        Point A;
        Point B;
        Point C;

        Segment AB;
        Segment BC;
        Segment CA;

        // Might be usefull later?
        float area() const;
    };

	// Quadrilateral, represented as two triangles (ABC and ACD). The summit A is at the "top left" of the quad, and the other summits are ordered clockwise.
    struct Quad {

        // Constructeurs
		Quad() : A({ 0, 0 }), B({ 0, 0 }), C({ 0, 0 }), D({ 0, 0 }),
            ABC(A, B, C),
            ACD(A, C, D) {
		}
        Quad(Point A, Point B, Point C, Point D) : A(A), B(B), C(C), D(D),
            ABC(A, B, C),
            ACD(A, C, D) {
        }

        Point A;
        Point B;
        Point C;
        Point D;

        Triangle ABC;
        Triangle ACD;

        bool collideWith(const Quad& otherQuad) const;

		float getMinX() const;
		float getMaxX() const;
		float getMinY() const;
		float getMaxY() const;

        // Might be usefull later?
        float area() const;

        string toString() const;
    };

    // On which side of the line is our point placed?
    float whichSide(const Point& p1, const Point& p2, const Point& p3);

    bool isPointInTriangle(const Point& P, const Triangle& T);

    // Only works for convex quads!
    bool isPointInQuad(const Point& P, const Quad& Q);

	Quad createQuad(Point center, int32 sizeX, int32 sizeY, int32 rotationDegrees);
	Quad createQuad(int32 x, int32 y, int32 sizeX, int32 sizeY, int32 rotationDegrees);
}