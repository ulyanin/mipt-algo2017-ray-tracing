//
// Created by ulyanin on 08.03.17.
//

#include "Triangle.h"

namespace Geometry
{

    Triangle::Triangle() :
        A_(Point()),
        B_(Point()),
        C_(Point()),
        surface(Surface())
    {

    }

    Triangle::Triangle(const Point &A, const Point &B, const Point &C) :
            A_(A),
            B_(B),
            C_(C),
            surface(A_, B_, C_)
    { }

    bool Triangle::intersection(const Ray &ray, Ray &normal) const
    {
        if (!surface.intersection(ray, normal))
            return false;
        return inside(normal.getBegin());
    }

    bool Triangle::inside(const Point &point) const
    {
        return betweenVectors(A_, B_, C_, point) &&
               betweenVectors(B_, C_, A_, point) &&
               betweenVectors(C_, A_, B_, point);
    }


    bool Triangle::betweenVectors(const Point &A, const Point &B, const Point &C, const Point &point)
    {
        Vector v1(B, A);
        Vector v2(C, A);
        Vector v(point, A);
        return greaterOrEqual(v1.crossProduct(v).dotProduct(v.crossProduct(v2)), 0);
    }

} //Geometry