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
    Illuminant(const Geometry::Point position);
    Geometry::Ray getRayTo(const Geometry::Point &p) const;
    static constexpr Geometry::Float SCALE_FACTOR = 200 * 1000.0;
protected:
    Geometry::Point position_;
};


#endif //MIPT_ALGO2017_RAY_TRACING_ILLUMINANT_H
