//
// Created by ulyanin on 13.03.17.
//

#include "Illuminant.h"

//const Geometry::Float Illuminant::SCALE_FACTOR = 100;

Illuminant::Illuminant(const Geometry::Point position):
    position_(position)
{ }

Geometry::Ray Illuminant::getRayTo(const Geometry::Point &p) const
{
    Geometry::Vector v(position_, p);
    return Geometry::Ray(position_, v.setLength(SCALE_FACTOR / v.length2()));
}
