//
// Created by ulyanin on 08.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_RAY_H
#define MIPT_ALGO2017_RAY_TRACING_RAY_H

#include "Point.h"
#include "Vector.h"

namespace Geometry
{
    class Ray
    {
    public:
        Ray();
        Ray(const Point &begin, const Vector &leading_vector);
        Point getBegin() const;
        void setBegin(const Point &begin);
        Vector getDirect() const;
        void setDirect(const Vector &direction);
    protected:
        Point p_;
        Vector v_;
    };
}

#endif //MIPT_ALGO2017_RAY_TRACING_RAY_H
