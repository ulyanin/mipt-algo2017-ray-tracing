//
// Created by ulyanin on 31.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_SURFACE_H
#define MIPT_ALGO2017_RAY_TRACING_SURFACE_H

#include "GeomFloat.h"
#include "Vector.h"
#include "Ray.h"

namespace Geometry
{
    class Surface
    {
    public:
        Surface();
        Surface(const Point &p1, const Point &p2, const Point &p3);
        bool intersection(const Ray &ray, Ray &normal) const;
        Float orientedDist(const Point &point) const;
        bool onSurface(const Point &p) const;

    protected:
        Vector normal_;
        Float D_;
    };

} // Geomatry


#endif //MIPT_ALGO2017_RAY_TRACING_SURFACE_H
