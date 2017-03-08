//
// Created by ulyanin on 07.03.17.
//

#include "Vector.h"

namespace Geometry
{

    Geometry::Vector::Vector(Geometry::Float x, Geometry::Float y, Geometry::Float z) :
            Point(x, y, z)
    {}

    Geometry::Vector::Vector(const Geometry::Point &point) :
            Point(point)
    {}

    Geometry::Vector Geometry::Vector::operator+(const Geometry::Vector &other) const
    {
        return Geometry::Vector(x_ + other.x_, y_ + other.y_, z_ + other.z_);
    }

    Geometry::Vector Geometry::Vector::operator-(const Geometry::Vector &other) const
    {
        return Geometry::Vector(x_ - other.x_, y_ - other.y_, z_ - other.z_);
    }

    Geometry::Float Geometry::Vector::dotProduct(const Geometry::Vector &other) const
    {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }

    Geometry::Vector Geometry::Vector::crossProduct(const Geometry::Vector &other) const
    {
        return Geometry::Vector(
                y_ * other.z_ - other.y_ * z_,
                -(x_ * other.z_ - z_ * other.x_),
                x_ * other.y_ - y_ * other.x_
        );
    }

    Geometry::Float
    Geometry::Vector::tripleProduct(const Geometry::Vector &a, const Geometry::Vector &b, const Geometry::Vector &c)
    {
        return a.dotProduct(b.crossProduct(c));  // (a * [b * c])
    }

    Geometry::Vector Geometry::Vector::norm() const
    {
        Float len = this->length();
        return Geometry::Vector(x_ / len, y_ / len, z_ / len);
    }

    Geometry::Float Geometry::Vector::length2() const
    {
        return Geometry::sqr(x_) + Geometry::sqr(y_) + Geometry::sqr(z_);
    }

    Geometry::Float Geometry::Vector::length() const
    {
        return Geometry::sqrt(this->length2());
    }

    Geometry::Vector Geometry::Vector::enlarge(Geometry::Float mul) const
    {
        return Geometry::Vector(x_ * mul, y_ * mul, z_ * mul);
    }

    Geometry::Vector Geometry::Vector::setLength(Geometry::Float len) const
    {
        return this->norm().enlarge(len);
    }

}