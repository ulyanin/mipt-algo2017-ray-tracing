//
// Created by ulyanin on 08.03.17.
//

#include "Ray.h"

namespace Geometry
{

    Ray::Ray() :
            p_(Point()),
            v_(Vector())
    {

    }

    Ray::Ray(const Point &begin, const Vector &leading_vector):
        p_(begin),
        v_(leading_vector)
    { }

    Point Ray::getBegin() const
    {
        return p_;
    }

    Vector Ray::getDirect() const
    {
        return v_;
    }

    void Ray::setBegin(const Point &begin)
    {
        p_ = begin;
    }

    void Ray::setDirect(const Vector &direction)
    {
        v_ = direction;
    }
}