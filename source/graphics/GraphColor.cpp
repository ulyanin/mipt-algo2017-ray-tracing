//
// Created by ulyanin on 13.04.17.
//

#include "GraphColor.h"

GraphColor::GraphColor(Geometry::Float brightness) :
        R_(brightness), G_(brightness), B_(brightness)
{

}

GraphColor::GraphColor(Geometry::Float R, Geometry::Float G, Geometry::Float B) :
        R_(R), G_(G), B_(B)
{

}

void GraphColor::setR(Geometry::Float R_)
{
    GraphColor::R_ = R_;
}

void GraphColor::setG(Geometry::Float G_)
{
    GraphColor::G_ = G_;
}

void GraphColor::setB(Geometry::Float B_)
{
    GraphColor::B_ = B_;
}

GraphColor GraphColor::enlarge(Geometry::Float intensity) const
{
    return GraphColor(R_ * intensity, G_ * intensity, B_ * intensity);
}

QColor GraphColor::toQTcolor() const
{
    return QColor((int)(R_ * 1),
                  (int)(G_ * 1),
                  (int)(B_ * 1));
}

GraphColor GraphColor::operator+(const GraphColor &other) const
{
    return GraphColor(R_ + other.R_,
                      G_ + other.G_,
                      B_ + other.B_);
}


