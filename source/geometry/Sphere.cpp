//
// Created by ulyanin on 08.03.17.
//

#include "Sphere.h"

namespace Geometry
{
    Sphere::Sphere():
            c_(Point()),
            r_(0)
    {}

    Sphere::Sphere(const Point &center, Float radius):
        c_(center),
        r_(radius)
    { }

    bool Sphere::hasIntersection(const Ray &ray) const
    {
        Ray tmp;
        return intersection(ray, tmp);
    }

    Float Sphere::distToRay(const Ray &ray) const
    {
        Vector v2(c_, ray.getBegin());
        Float area = v2.crossProduct(ray.getDirect()).length();
        return area / ray.getDirect().length();
    }

    bool Sphere::intersection(const Ray &ray, Ray &normal) const
    {
        if (lessOrEqual(Vector(ray.getBegin(), c_).length2(), r_)) {
            // if inside a sphere we think that there is no intersection
            return 0;
        }
        Float d = distToRay(ray);
        if (greater(d, r_)) {
            return 0;
        }
        Vector v2(ray.getBegin(), c_);
        if (lessOrEqual(v2.dotProduct(ray.getDirect()), 0)) {
            // ray has direction against the sphere
            return 0;
        }
        Vector norm = ray.getDirect().crossProduct(v2);
        Vector norm_line = ray.getDirect().crossProduct(norm).setLength(d);
        Point between = c_ + norm_line;
        Float a = Geometry::sqrt(Geometry::sqr(r_) - Geometry::sqr(d));
//        p1 = between - ray.getDirect().setLength(a);
//        p2 = between + ray.getDirect().setLength(a);
        normal.setBegin(between - ray.getDirect().setLength(a));
        normal.setDirect(Vector(c_, normal.getBegin()).norm());
        if (equal(d, r_)) {
            return 1;
        }
        return 2;
    }

}