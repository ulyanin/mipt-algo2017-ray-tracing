//
// Created by ulyanin on 04.04.17.
//

#include "GraphQuadrangle.h"


GraphQuadrangle::GraphQuadrangle() :
    IGraphObject(),
    Quadrangle()
{ }

GraphQuadrangle::GraphQuadrangle(const Geometry::Point &A,
                                 const Geometry::Point &B,
                                 const Geometry::Point &C,
                                 const Geometry::Point &D,
                                 const GraphMaterial &material) :
        IGraphObject(Geometry::BoundingBox({A, B, C, D}), material),
        Quadrangle(A, B, C, D)
{ }


bool GraphQuadrangle::insideABox(const Geometry::BoundingBox &boundingBox) const
{
    return
            boundingBox.isInside(A_) ||
            boundingBox.isInside(B_) ||
            boundingBox.isInside(C_) ||
            boundingBox.isInside(D_);
}

bool GraphQuadrangle::intersection(const Geometry::Ray &ray, Geometry::Ray &normal) const
{
    return Geometry::Quadrangle::intersection(ray, normal);
}

