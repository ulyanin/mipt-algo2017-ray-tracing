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
//        if (!surface.intersection(ray, normal))
//            return false;

        //Find vectors for two edges sharing V1
        Vector e1(A_, B_), e2(A_, C_);
        Geometry::Float det, inv_det, u, v;
        Geometry::Float t;

//        e1 = p2 - p1;
//        e2 = p3 - p1;

        //Begin calculating determinant - also used to calculate u parameter
        Vector P = ray.getDirect().crossProduct(e2);
        //if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
        det = e1.dotProduct(P);
        //NOT CULLING
        if (det > -TRIANGLE_EPS && det < TRIANGLE_EPS) {
            return false;
        }
        inv_det = 1 / det;

        //calculate distance from V1 to ray origin
        Vector T(A_, ray.getBegin());

        //Calculate u parameter and test bound
        u = T.dotProduct(P) * inv_det;
        //The intersection lies outside of the triangle
        if (u < 0 || u > 1) {
            return false;
        }

        //Prepare to test v parameter
        Vector Q = T.crossProduct(e1);

        //Calculate V parameter and test bound
        v = ray.getDirect().dotProduct(Q) * inv_det;

        //The intersection lies outside of the triangle
        if (v < 0 || u + v  > 1) {
            return false;
        }

        t = e2.dotProduct(Q) * inv_det;

        if (t > TRIANGLE_EPS) { //ray intersection
            Vector norm = e1.crossProduct(e2).norm();
            normal.setBegin(ray.getBegin() + ray.getDirect().enlarge(t));
            if (norm.dotProduct(ray.getDirect()) < 0) {
                normal.setDirect(norm);
            }
            else {
                normal.setDirect(norm.enlarge(-1));
            }
            return true;
        }

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
        Vector v2(B, C);
        Vector v(point, B);
        return greaterOrEqual(v1.crossProduct(v).dotProduct(v.crossProduct(v2)), 0);
    }

} //Geometry