//
// Created by ulyanin on 13.03.17.
//

#include "GraphSphere.h"

GraphSphere::GraphSphere() :
        Sphere()
{
    boundingBox_ = Geometry::BoundingBox();
}

GraphSphere::GraphSphere(const Geometry::Point &center, const Geometry::Float r) :
        Sphere(center, r)
{
    Geometry::Vector rVector(r, r, r);
    boundingBox_ = Geometry::BoundingBox(center - rVector, center + rVector);
};

bool GraphSphere::intersection(const Geometry::Ray &ray, Geometry::Ray &normal) const
{
    return Geometry::Sphere::intersection(ray, normal);
}

bool GraphSphere::insideABox(const Geometry::BoundingBox &boundingBox) const
{
    Geometry::Vector v1(boundingBox.getPMin(), c_);
    Geometry::Vector v2(c_, boundingBox.getPMax());
    return
            v1.getX() > 0 && v1.getY() > 0 && v1.getZ() > 0 &&
            v2.getX() > 0 && v2.getY() > 0 && v2.getZ() > 0;

}
