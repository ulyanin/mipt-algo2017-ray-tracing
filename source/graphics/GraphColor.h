//
// Created by ulyanin on 13.04.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_GRAPHCOLOR_H
#define MIPT_ALGO2017_RAY_TRACING_GRAPHCOLOR_H


#include <QtGui/QColor>
#include "../geometry/GeomFloat.h"

class GraphColor
{
public:
    explicit GraphColor(Geometry::Float brightness=1);

    explicit GraphColor(Geometry::Float R, Geometry::Float G, Geometry::Float B);

    void setR(Geometry::Float R_);

    void setG(Geometry::Float G_);

    void setB(Geometry::Float B_);

    GraphColor enlarge(Geometry::Float intensity) const;

    GraphColor operator+(const GraphColor &other) const;

    QColor toQTcolor() const;


protected:
    Geometry::Float R_, G_, B_;
};


#endif //MIPT_ALGO2017_RAY_TRACING_GRAPHCOLOR_H
