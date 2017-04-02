//
// Created by ulyanin on 08.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_SPHERE_H
#define MIPT_ALGO2017_RAY_TRACING_SPHERE_H

#include "Point.h"
#include "Ray.h"

namespace Geometry
{
    class Sphere
    {
    public:
        Sphere();

        Sphere(const Point &center, Float radius);

        Float distToRay(const Ray &ray) const;

        bool hasIntersection(const Ray &ray) const;

        bool intersection(const Ray &ray, Ray &normal) const;

    private:
        Point c_;
        Float r_;
    };
}

#endif //MIPT_ALGO2017_RAY_TRACING_SPHERE_H
