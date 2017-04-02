//
// Created by ulyanin on 08.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_TRIANGLE_H
#define MIPT_ALGO2017_RAY_TRACING_TRIANGLE_H

#include "Point.h"
#include "Ray.h"
#include "Surface.h"

namespace Geometry
{
    class Triangle
    {
    public:
        Triangle();

        Triangle(const Point &A, const Point &B, const Point &C);

        bool intersection(const Ray &ray, Ray &normal) const;

        bool inside(const Point &point) const;

        static bool betweenVectors(const Point &A, const Point &B, const Point &C, const Point &point);
    protected:
        Point A_, B_, C_;
        Surface surface;
    };

} //Geometry

#endif //MIPT_ALGO2017_RAY_TRACING_TRIANGLE_H
