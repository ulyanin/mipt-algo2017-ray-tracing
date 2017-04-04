//
// Created by ulyanin on 04.04.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_GRAPH_QUADRANGLE_H
#define MIPT_ALGO2017_RAY_TRACING_GRAPH_QUADRANGLE_H


#include "../geometry/Quadrangle.h"
#include "IGraphObject.h"

class GraphQuadrangle :
        public IGraphObject,
        public Geometry::Quadrangle
{
public:
    GraphQuadrangle();

    GraphQuadrangle(const Geometry::Point &A,
                    const Geometry::Point &B,
                    const Geometry::Point &C,
                    const Geometry::Point &D);

    virtual bool intersection(const Geometry::Ray &ray, Geometry::Ray &normal);

protected:
};

#endif //MIPT_ALGO2017_RAY_TRACING_GRAPH_QUADRANGLE_H
