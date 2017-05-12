//
// Created by ulyanin on 13.04.17.
//

#include "GraphMaterial.h"

GraphMaterial::GraphMaterial(const std::string &name) :
        name_(name),
        color_(GraphColor()),
        alpha_(1),
        reflect_(0),
        refract_(1)
{

}

GraphMaterial::GraphMaterial(const std::string &name, const GraphColor &color,
                             const Geometry::Float &alpha, const Geometry::Float &reflect,
                             const Geometry::Float &refract) :
        name_(name),
        color_(color),
        alpha_(alpha),
        reflect_(reflect),
        refract_(refract)
{

}

const std::string &GraphMaterial::getName() const
{
    return name_;
}

GraphColor GraphMaterial::getColor() const
{
    return color_;
}

Geometry::Float GraphMaterial::getReflect() const
{
    return reflect_;
}

Geometry::Float GraphMaterial::getRefract() const
{
    return refract_;
}

Geometry::Float GraphMaterial::getAlpha() const
{
    return alpha_;
}
