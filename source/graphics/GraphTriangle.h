//
// Created by ulyanin on 31.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_GRAPHTRIANGLE_H
#define MIPT_ALGO2017_RAY_TRACING_GRAPHTRIANGLE_H

#include "IGraphObject.h"
#include "../geometry/Triangle.h"

class GraphTriangle :
        public IGraphObject,
        public Geometry::Triangle
{
public:
    GraphTriangle();

    GraphTriangle(const Geometry::Point &A,
                  const Geometry::Point &B,
                  const Geometry::Point &C);

    virtual bool intersection(const Geometry::Ray &ray, Geometry::Ray &normal) const;

    virtual bool insideABox(const Geometry::BoundingBox &boundingBox) const;

protected:
};


#endif //MIPT_ALGO2017_RAY_TRACING_GRAPHTRIANGLE_H
