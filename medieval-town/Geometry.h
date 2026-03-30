#pragma once

///// Let's do some geometry! /////
namespace Geometry {

    // This represents each point of our geometric shapes.
    struct Point {
        float x = 0.0f;
        float y = 0.0f;
    };

    // Trace a line between two points.
    struct Segment {
        Point p1;
        Point p2;

        float Length() const;
    };

    // Basic triangle.
    struct Triangle {

        Triangle(Point A, Point B, Point C) {

            this->A = A;
            this->B = B;
            this->C = C;

            AB = { A, B };
            BC = { B, C };
            CA = { C, A };
        }

        Point A;
        Point B;
        Point C;

        Segment AB;
        Segment BC;
        Segment CA;

        // Might be usefull later?
        float Area() const;
    };

    // Trace a Quad.
    struct Quad {

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

        // Might be usefull later?
        float Area() const;

    };

    // On which side of the line is our point placed?
    float WhichSide(const Point& p1, const Point& p2, const Point& p3);

    bool IsPointInTriangle(const Point& P, const Triangle& T);

    // !By the way: the following only works for convex quads!
    bool IsPointInQuad(const Point& P, const Quad& Q);
}