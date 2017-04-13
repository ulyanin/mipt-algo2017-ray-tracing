//
// Created by ulyanin on 13.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_GRAPHSPHERE_H
#define MIPT_ALGO2017_RAY_TRACING_GRAPHSPHERE_H

#include "../geometry/Sphere.h"
#include "IGraphObject.h"

class GraphSphere:
        public IGraphObject,
        public Geometry::Sphere
{
public:

    GraphSphere();

    GraphSphere(const Geometry::Point &center,
                const Geometry::Float radius,
                const GraphMaterial &material);

    virtual bool intersection(const Geometry::Ray &ray, Geometry::Ray &normal) const;

    virtual bool insideABox(const Geometry::BoundingBox &boundingBox) const;

protected:
};


#endif //MIPT_ALGO2017_RAY_TRACING_GRAPHSPHERE_H
