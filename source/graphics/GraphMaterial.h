//
// Created by ulyanin on 13.04.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_GRAPHMATERIAL_H
#define MIPT_ALGO2017_RAY_TRACING_GRAPHMATERIAL_H


#include "GraphColor.h"

class GraphMaterial
{
public:
    GraphMaterial(const std::string &name);

    GraphMaterial(const std::string &name,
                  const GraphColor &color,
                  const Geometry::Float &alpha=1,
                  const Geometry::Float &reflect=0,
                  const Geometry::Float &refract=1);

protected:
    std::string name_;
    GraphColor color_;
    Geometry::Float alpha_;
    Geometry::Float reflect_;
    Geometry::Float refract_;
};


#endif //MIPT_ALGO2017_RAY_TRACING_GRAPHMATERIAL_H
