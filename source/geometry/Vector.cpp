//
// Created by ulyanin on 07.03.17.
//

#include "Vector.h"

Geometry::Vector::Vector(GeomFloat::Float x, GeomFloat::Float y, GeomFloat::Float z):
        x_(x),
        y_(y),
        z_(z)
{ }

Geometry::Vector Geometry::Vector::operator+(const Geometry::Vector &other) const
{
    return Geometry::Vector(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

Geometry::Vector Geometry::Vector::operator-(const Geometry::Vector &other) const
{
    return Geometry::Vector(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

GeomFloat::Float Geometry::Vector::dotProduct(const Geometry::Vector &other) const
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

GeomFloat::Float
Geometry::Vector::tripleProduct(const Geometry::Vector &a, const Geometry::Vector &b, const Geometry::Vector &c)
{
    return a.dotProduct(b.crossProduct(c));  // (a * [b * c])
}

Geometry::Vector Geometry::Vector::norm() const
{
    Float len = this->length();
    return Geometry::Vector(x_ / len, y_ / len, z_ / len);
}

GeomFloat::Float Geometry::Vector::length2() const
{
    return GeomFloat::sqr(x_) + GeomFloat::sqr(y_) + GeomFloat::sqr(z_);
}

GeomFloat::Float Geometry::Vector::length() const
{
    return GeomFloat::sqrt(this->length2());
}

Geometry::Vector Geometry::Vector::enlarge(GeomFloat::Float mul) const
{
    return Geometry::Vector(x_ * mul, y_ * mul, z_ * mul);
}

Geometry::Vector Geometry::Vector::setLength(GeomFloat::Float len) const
{
    return this->norm().enlarge(len);
}
