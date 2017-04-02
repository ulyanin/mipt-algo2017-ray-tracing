//
// Created by ulyanin on 07.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_FLOAT_H
#define MIPT_ALGO2017_RAY_TRACING_FLOAT_H

#include <cmath>
#include <iostream>
#include <algorithm>

namespace Geometry
{
    typedef double Float;

    const Float EPS = 1e-8;

    inline Float absGeomFloat(Float f)
    {
        return std::abs(f);
    }

    template <class T>
    inline T sqr(const T& v)
    {
        return v * v;
    }

    inline Float sqrt(Float value)
    {
        return std::sqrt(value);
    }

    inline bool equal(Float a, Float b)
    {
        return absGeomFloat(a - b) < EPS;
    }


    inline bool less(Float a, Float b)
    {
        return a + EPS < b;
    }


    inline bool lessOrEqual(Float a, Float b)
    {
        return a < b + EPS;
    }

    inline bool greater(Float a, Float b)
    {
        return less(b, a);
    }

    inline bool greaterOrEqual(Float a, Float b)
    {
        return lessOrEqual(b, a);
    }

    inline int sign(Float f)
    {
        if (greater(f, 0))
            return 1;
        if (less(f, 0))
            return -1;
        return 0;
    }


} //Geometry


#endif //MIPT_ALGO2017_RAY_TRACING_FLOAT_H
