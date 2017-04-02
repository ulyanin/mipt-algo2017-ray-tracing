//
// Created by ulyanin on 13.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_ILLUMINANT_H
#define MIPT_ALGO2017_RAY_TRACING_ILLUMINANT_H

#include "../geometry/Point.h"

class Illuminant
{
public:
    Illuminant(const Geometry::Point position);
protected:
    Geometry::Point position_;
};


#endif //MIPT_ALGO2017_RAY_TRACING_ILLUMINANT_H
