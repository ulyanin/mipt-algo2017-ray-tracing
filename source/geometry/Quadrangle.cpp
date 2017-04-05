//
// Created by ulyanin on 31.03.17.
//

#include "Quadrangle.h"

namespace Geometry {


    Quadrangle::Quadrangle() :
        Triangle(),
        D_(Point())
    {

    }

    Quadrangle::Quadrangle(const Point &A, const Point &B, const Point &C, const Point &D) :
        Triangle(A, B, C),
        D_(D)
    {

    }

    bool Quadrangle::inside(const Point &point) const
    {

        return Triangle::betweenVectors(A_, B_, C_, point) &&
               Triangle::betweenVectors(B_, C_, D_, point) &&
               Triangle::betweenVectors(C_, D_, A_, point) &&
               Triangle::betweenVectors(D_, A_, B_, point);
    }

    bool Quadrangle::intersection(const Ray &ray, Ray &normal) const
    {
        if (Triangle::intersection(ray, normal)) {
            return true;
        }
        return Triangle(C_, D_, A_).intersection(ray, normal);
    }

}