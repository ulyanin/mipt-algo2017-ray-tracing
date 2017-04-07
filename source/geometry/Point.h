//
// Created by ulyanin on 08.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_POINT_H
#define MIPT_ALGO2017_RAY_TRACING_POINT_H

#include "GeomFloat.h"
#include <fstream>

namespace Geometry
{
    class Vector;

    class Point
    {
    public:
        explicit Point(Float x=0, Float y=0, Float z=0);
        Point(const Point &p) = default;

        Point operator+(const Point &p) const;
        Vector operator-(const Point &p) const;

        Point operator+(const Vector &v) const;
        Point operator-(const Vector &v) const;

        bool operator==(const Point &other) const;

        Float getX() const;
        Float getY() const;
        Float getZ() const;

        void setX(const Float &xValue);

        void setY(const Float &yValue);

        void setZ(const Float &zValue);


        Float getAxisCoordinate(int axisNumber) const;
        void setAxis(int axisNumber, const Float &value);

        friend std::istream&operator>>(std::istream &is, Point &point);
        friend std::ostream&operator<<(std::ostream &os, const Point &point);

    protected:
        Float x_, y_, z_;
    };

}


#endif //MIPT_ALGO2017_RAY_TRACING_POINT_H
