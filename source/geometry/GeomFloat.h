//
// Created by ulyanin on 07.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_FLOAT_H
#define MIPT_ALGO2017_RAY_TRACING_FLOAT_H

#include <cmath>

namespace GeomFloat
{
    typedef double Float;


    const Float EPS = 1e-8;

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
        return fabsl(a - b) < EPS;
    }


    inline bool less(Float a, Float b) {
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

} //GeomFloat


#endif //MIPT_ALGO2017_RAY_TRACING_FLOAT_H
