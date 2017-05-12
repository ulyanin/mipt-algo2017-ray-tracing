//
// Created by ulyanin on 05.04.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_GRAPHSCREEN_H
#define MIPT_ALGO2017_RAY_TRACING_GRAPHSCREEN_H


#include "../geometry/Point.h"
#include "../geometry/Vector.h"

class GraphScreen
{
public:
    GraphScreen() = default;

    GraphScreen(const Geometry::Point &origin,
                const Geometry::Point &vertex,
                const Geometry::Vector xEdge,
                const Geometry::Vector yEdge,
                int resolutionX=500, int resolutionY=500);

    GraphScreen(const GraphScreen &other) = default;

    Geometry::Point getPoint(int x, int y) const;
    int getResolutionWidth() const;
    int getResolutionHeight() const;
    Geometry::Vector getNormal() const;
protected:
    Geometry::Point origin_;
    Geometry::Point vertex_;
    Geometry::Vector xEdge_, yEdge_;
    int resolutionWidth_;
    int resolutionHeight_;
};


#endif //MIPT_ALGO2017_RAY_TRACING_GRAPHSCREEN_H
