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
        friend std::ostream&operator<<(std::ostream &os, const Point &point);
    protected:
        Float x_, y_, z_;
    };
}


#endif //MIPT_ALGO2017_RAY_TRACING_POINT_H
