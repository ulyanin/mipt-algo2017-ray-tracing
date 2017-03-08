//
// Created by ulyanin on 08.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_TRIANGLE_H
#define MIPT_ALGO2017_RAY_TRACING_TRIANGLE_H

#include "Point.h"

namespace Geometry
{
    class Triangle
    {
    public:
        Triangle(const Point &A, const Point &B, const Point &C);
    protected:
        Point A_, B_, C_;
    };

} //Geometry

#endif //MIPT_ALGO2017_RAY_TRACING_TRIANGLE_H
