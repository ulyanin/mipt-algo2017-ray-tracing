//
// Created by ulyanin on 07.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_VECTOR_H
#define MIPT_ALGO2017_RAY_TRACING_VECTOR_H

#include "GeomFloat.h"

namespace Geometry {

    using GeomFloat::Float;

    class Vector
    {
    public:
        explicit Vector(Float x = 0, Float y = 0, Float z = 0);
        Vector operator+(const Vector &other) const;
        Vector operator-(const Vector &other) const;
        Float dotProduct(const Vector &other) const;
        Vector crossProduct(const Vector &other) const;
        static Float tripleProduct(const Vector &a, const Vector &b, const Vector &c);
        Float length2() const;
        Float length() const;
        Vector norm() const;
        Vector enlarge(Float mul) const;
        Vector setLength(Float len) const;

    protected:
        Float x_, y_, z_;
    };


}//Geometry


#endif //MIPT_ALGO2017_RAY_TRACING_VECTOR_H
