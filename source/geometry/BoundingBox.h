//
// Created by ulyanin on 06.04.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_BOUNDINGBOX_H
#define MIPT_ALGO2017_RAY_TRACING_BOUNDINGBOX_H


#include <vector>
#include <array>
#include "Point.h"
#include "Vector.h"
#include "Ray.h"

namespace Geometry
{
    class BoundingBox
    {
    public:
        BoundingBox(const Point &pointMin = Point(),
                    const Point &pointMax = Point());

        BoundingBox(std::initializer_list<Point> initializerList);

        const Point &getPMin() const;

        const Point &getPMax() const;

        Float getLengthAlongAxis(int axisNumber) const;

        std::pair<BoundingBox, BoundingBox> split(int axis, Float coordinate) const;

        static std::array<Geometry::Vector, 3> AXISES;

        Float getSurfaceArea() const;
        Float getVolume() const;


        bool isInside(const Point &p) const;

        bool intersection(const Ray &ray, Ray &normal) const;

    protected:
        Point pMin_, pMax_;
    };
}


#endif //MIPT_ALGO2017_RAY_TRACING_BOUNDINGBOX_H
