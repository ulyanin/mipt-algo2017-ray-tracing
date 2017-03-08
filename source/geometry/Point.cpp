//
// Created by ulyanin on 08.03.17.
//

#include "Point.h"
#include "Vector.h"

namespace Geometry
{
    Geometry::Point::Point(Geometry::Float x, Geometry::Float y, Geometry::Float z) :
            x_(x),
            y_(y),
            z_(z)
    {}

    std::ostream &operator<<(std::ostream &os, const Geometry::Point &point)
    {
        os << "(" << point.x_ << " " << point.y_ << " " << point.z_ << ")";
        return os;
    }
}
