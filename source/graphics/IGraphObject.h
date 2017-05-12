//
// Created by ulyanin on 13.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_IGRAPHOBJECT_H
#define MIPT_ALGO2017_RAY_TRACING_IGRAPHOBJECT_H

#include <vector>
#include "../geometry/Ray.h"
#include "../geometry/BoundingBox.h"
#include "GraphMaterial.h"


class IGraphObject
{
public:
    IGraphObject();

    IGraphObject(const Geometry::BoundingBox &boundingBox,
                 const GraphMaterial &material);

    virtual bool intersection(const Geometry::Ray& ray, Geometry::Ray &normal) const = 0;

    virtual bool insideABox(const Geometry::BoundingBox &boundingBox) const = 0;

    virtual Geometry::Float getMinimumAlongAxis(int axisNumber) const;

    virtual Geometry::Float getMaximumAlongAxis(int axisNumber) const;
    
    virtual Geometry::BoundingBox getBoundingBox() const;

    virtual GraphMaterial getMaterial() const;

protected:
    Geometry::BoundingBox boundingBox_;
    GraphMaterial material_;
};


#endif //MIPT_ALGO2017_RAY_TRACING_IGRAPHOBJECT_H
