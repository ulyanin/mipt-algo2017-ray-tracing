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
                             const Geometry::Point &C) :
        Triangle(A, B, C)
{

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

