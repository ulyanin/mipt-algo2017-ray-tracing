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

    Point Point::operator+(const Vector &v) const
    {
        return Point(x_ + v.x_, y_ + v.y_, z_ + v.z_);
    }

    Point Point::operator-(const Vector &v) const
    {
        return Point(x_ - v.x_, y_ - v.y_, z_ - v.z_);
    }

    Float Point::getX() const
    {
        return x_;
    }

    Float Point::getY() const
    {
        return y_;
    }

    Float Point::getZ() const
    {
        return z_;
    }

    Point Point::operator+(const Point &p) const
    {
        return Point(x_ + p.x_, y_ + p.y_, z_ + p.z_);
    }

    Vector Point::operator-(const Point &p) const
    {
        return Vector(x_ - p.x_, y_ - p.y_, z_ - p.z_);
    }

    bool Point::operator==(const Point &other) const
    {
        return Geometry::equal(Vector(other, *this).length2(), 0);
    }
}
