//
// Created by ulyanin on 08.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_SPHERE_H
#define MIPT_ALGO2017_RAY_TRACING_SPHERE_H

#include "Point.h"

namespace Geometry
{
    class Sphere
    {
    public:
        Sphere(Point center, Float radius);
    private:
        Point c_;
        Float r_;
    };
}

#endif //MIPT_ALGO2017_RAY_TRACING_SPHERE_H
