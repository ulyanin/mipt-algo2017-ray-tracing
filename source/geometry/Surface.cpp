//
// Created by ulyanin on 31.03.17.
//

#include "Surface.h"

namespace Geometry
{

    Surface::Surface(const Point &p1, const Point &p2, const Point &p3) :
        normal_(Vector(p2, p1).crossProduct(Vector(p3, p1)).norm()),
        D_(-(normal_.dotProduct(Vector(p1))))
    { }

    bool Surface::intersection(const Ray &ray, Ray &normal) const
    {
        Float cosAlpha = ray.getDirect().norm().dotProduct(normal_);
        if (equal(cosAlpha, 0)) {
            return false;
        }
        Float h = orientedDist(ray.getBegin());
        Float len = h / Geometry::absGeomFloat(cosAlpha);
        normal.setBegin(
                ray.getBegin() +
                        ray.getDirect().setLength(Geometry::absGeomFloat(len))
        );
        normal.setDirect(normal_.norm());
//        normal.setDirect(normal_.enlarge(-sign(cosAlpha)));
        return onSurface(normal.getBegin());
    }

    Float Surface::orientedDist(const Point &point) const
    {
        return normal_.dotProduct(Vector(point)) + D_;
    }

    bool Surface::onSurface(const Point &p) const
    {
        return Geometry::equal(orientedDist(p), 0);
    }

    Surface::Surface() :
        normal_(Vector()),
        D_(0)
    { }

    Surface::Surface(const Point &p, const Vector &normal) :
            normal_(normal),
            D_(-normal.dotProduct(Vector(p)))
    {

    }

}