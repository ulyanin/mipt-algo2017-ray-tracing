//
// Created by ulyanin on 13.03.17.
//

#include "GraphSphere.h"

GraphSphere::GraphSphere() :
        Sphere()
{

}

GraphSphere::GraphSphere(const Geometry::Point &center, const Geometry::Float r) :
        Sphere(center, r)
{

}

bool GraphSphere::intersection(const Geometry::Ray &ray, Geometry::Ray &normal)
{
    return Geometry::Sphere::intersection(ray, normal);
}
