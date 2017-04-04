//
// Created by ulyanin on 31.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_QUADRANGLE_H
#define MIPT_ALGO2017_RAY_TRACING_QUADRANGLE_H


#include "Point.h"
#include "Triangle.h"

namespace Geometry {

    class Quadrangle : public Triangle
    {
    public:
        Quadrangle();
        Quadrangle(const Point &A, const Point &B, const Point &C, const Point &D);
        virtual bool inside(const Point &point) const;
    protected:
        Point D_;
    };

} // Geometry


#endif //MIPT_ALGO2017_RAY_TRACING_QUADRANGLE_H
