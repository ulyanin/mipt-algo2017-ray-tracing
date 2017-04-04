//
// Created by ulyanin on 04.04.17.
//

#include "GraphQuadrangle.h"

GraphQuadrangle::GraphQuadrangle() :
    Quadrangle()
{

}

GraphQuadrangle::GraphQuadrangle(const Geometry::Point &A,
                                 const Geometry::Point &B,
                                 const Geometry::Point &C,
                                 const Geometry::Point &D) :
        Quadrangle(A, B, C, D)
{

}

bool GraphQuadrangle::intersection(const Geometry::Ray &ray, Geometry::Ray &normal)
{
    return Geometry::Quadrangle::intersection(ray, normal);
}
