//
// Created by ulyanin on 31.03.17.
//

#include "GraphTriangle.h"

GraphTriangle::GraphTriangle() :
    Triangle()
{
}

GraphTriangle::GraphTriangle(const Geometry::Point &A,
                             const Geometry::Point &B,
                             const Geometry::Point &C,
                             const GraphMaterial &material) :
        Triangle(A, B, C),
        material_(material)
{
    boundingBox_ = {A_, B_, C_};
}

bool GraphTriangle::intersection(const Geometry::Ray &ray, Geometry::Ray &normal) const
{
    return Geometry::Triangle::intersection(ray, normal);
}

bool GraphTriangle::insideABox(const Geometry::BoundingBox &boundingBox) const
{
    return
            boundingBox.isInside(A_) ||
            boundingBox.isInside(B_) ||
            boundingBox.isInside(C_);
}

