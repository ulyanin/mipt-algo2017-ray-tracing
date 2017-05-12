//
// Created by ulyanin on 13.04.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_GRAPHMATERIAL_H
#define MIPT_ALGO2017_RAY_TRACING_GRAPHMATERIAL_H


#include <QtGui/QColor>
#include "GraphColor.h"

class GraphMaterial
{
public:
    GraphMaterial(const std::string &name="");

    GraphMaterial(const std::string &name,
                  const GraphColor &color,
                  const Geometry::Float &alpha=1,
                  const Geometry::Float &reflect=0,
                  const Geometry::Float &refract=1);

    const std::string &getName() const;
    GraphColor getColor() const;

protected:
    std::string name_;
    GraphColor color_;
    Geometry::Float alpha_;
    Geometry::Float reflect_;
public:
    Geometry::Float getReflect() const;
    Geometry::Float getRefract() const;
    Geometry::Float getAlpha() const;

protected:
    Geometry::Float refract_;
};


#endif //MIPT_ALGO2017_RAY_TRACING_GRAPHMATERIAL_H
