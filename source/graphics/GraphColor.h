//
// Created by ulyanin on 13.04.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_GRAPHCOLOR_H
#define MIPT_ALGO2017_RAY_TRACING_GRAPHCOLOR_H


#include "../geometry/GeomFloat.h"

class GraphColor
{
public:
    explicit GraphColor(int brightness=255);

    explicit GraphColor(int R, int G, int B);

    void setR(Geometry::Float R_);

    void setG(Geometry::Float G_);

    void setB(Geometry::Float B_);

protected:
    Geometry::Float R_, G_, B_;
};


#endif //MIPT_ALGO2017_RAY_TRACING_GRAPHCOLOR_H
