//
// Created by ulyanin on 13.04.17.
//

#include "GraphColor.h"

GraphColor::GraphColor(int brightness) :
        R_(brightness), G_(brightness), B_(brightness)
{

}

GraphColor::GraphColor(int R, int G, int B) :
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


