//
// Created by ulyanin on 05.04.17.
//

#include "GraphScreen.h"

GraphScreen::GraphScreen(const Geometry::Point &origin,
                         const Geometry::Point &vertex,
                         const Geometry::Vector xEdge, const Geometry::Vector yEdge,
                         int resolutionX, int resolutionY) :
        origin_(origin),
        vertex_(vertex),
        xEdge_(xEdge.enlarge(1 / static_cast<Geometry::Float >(resolutionX))),
        yEdge_(yEdge.enlarge(1 / static_cast<Geometry::Float >(resolutionY))),
        resolutionWidth_(resolutionX),
        resolutionHeight_(resolutionY)
{

}

Geometry::Point GraphScreen::getPoint(int x, int y) const
{
    return (vertex_ + xEdge_.enlarge(x)) + yEdge_.enlarge(y);
}

int GraphScreen::getResolutionWidth() const
{
    return resolutionWidth_;
}

int GraphScreen::getResolutionHeight() const
{
    return resolutionHeight_;
}

Geometry::Vector GraphScreen::getNormal() const
{
    return yEdge_.crossProduct(xEdge_).norm();
}

const Geometry::Point &GraphScreen::getOrigin() const
{
    return origin_;
}

void GraphScreen::setResolution(int resolutionWidth, int resolutionHeight)
{
    resolutionWidth_ = resolutionWidth;
    resolutionHeight_ = resolutionHeight;
}



