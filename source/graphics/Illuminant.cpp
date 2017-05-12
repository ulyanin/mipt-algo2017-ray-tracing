//
// Created by ulyanin on 13.03.17.
//

#include "Illuminant.h"

//const Geometry::Float Illuminant::SCALE_FACTOR = 100;

Illuminant::Illuminant(const Geometry::Point position, Geometry::Float scale_factor):
    position_(position),
    SCALE_FACTOR(scale_factor)
{ }

Geometry::Ray Illuminant::getRayTo(const Geometry::Point &p) const
{
    Geometry::Vector v(position_, p);
//    v = v.setLength(SCALE_FACTOR / v.length2());
    v = v.setLength(1);
    return Geometry::Ray(position_, v);
}
