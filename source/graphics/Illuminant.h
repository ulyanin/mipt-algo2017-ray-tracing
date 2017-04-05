//
// Created by ulyanin on 13.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_ILLUMINANT_H
#define MIPT_ALGO2017_RAY_TRACING_ILLUMINANT_H

#include "../geometry/Point.h"
#include "../geometry/Ray.h"

class Illuminant
{
public:
    Illuminant(const Geometry::Point position, Geometry::Float scale_factor=1000 * 50.0);
    Geometry::Ray getRayTo(const Geometry::Point &p) const;
protected:
    Geometry::Float SCALE_FACTOR = 1000 * 50.0;
    Geometry::Point position_;
};


#endif //MIPT_ALGO2017_RAY_TRACING_ILLUMINANT_H
