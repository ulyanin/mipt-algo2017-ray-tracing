//
// Created by ulyanin on 13.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_IGRAPHOBJECT_H
#define MIPT_ALGO2017_RAY_TRACING_IGRAPHOBJECT_H

#include <vector>
#include "../geometry/Ray.h"

class IGraphObject
{
public:
    virtual bool intersection(const Geometry::Ray& ray, Geometry::Ray &normal) = 0;

protected:

};


#endif //MIPT_ALGO2017_RAY_TRACING_IGRAPHOBJECT_H
