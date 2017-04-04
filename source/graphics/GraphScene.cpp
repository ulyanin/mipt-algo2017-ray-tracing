//
// Created by ulyanin on 13.03.17.
//

#include <iostream>
#include "GraphScene.h"
#include "../geometry/Ray.h"

GraphScene::GraphScene(QObject * parent) :
        scene_(parent),
        view_(&scene_)
{
    scene_.setBackgroundBrush(QColor(0, 0, 0));
}

void GraphScene::addObject(IGraphObject * object)
{
    objects_.push_back(object);
}

void GraphScene::drawScene()
{
    int width = 1000;
    int height = 800;
    for (int x = -50; x < width; ++x) {
        for (int y = -50; y < height; ++y) {
            Geometry::Ray ray(Geometry::Point(x, y, 0), Geometry::Vector(0, 0, 1));
            drawPoint(x, y, traceRay(ray));
        }
    }
    view_.show();
}

QColor GraphScene::calcColor(const Geometry::Ray &normal) const
{
    Geometry::Vector vectorIntensity;
    for (Illuminant* illuminant : illuminants) {
        Geometry::Ray rayDirect = illuminant->getRayTo(normal.getBegin());
        Geometry::Ray traced = traceRay(rayDirect);
        if (traced.getDirect().isNull()) {
            continue;
        }
        if (traced.getBegin() == normal.getBegin()) {
            vectorIntensity += normal.getDirect().getProjection(rayDirect.getDirect());
        }
    }
//    std::cout << vectorIntensity.length2() << std::endl;
    int brightness = (int)(255 * std::min((Geometry::Float)1, vectorIntensity.length2()));
    if (brightness < 0) {
        std::cerr << "wrong brightness" << std::endl;
    }
    brightness = std::max(brightness, 0);
    brightness = abs(brightness);
    return QColor(brightness, brightness, brightness);
}

void GraphScene::drawPoint(int x, int y, const Geometry::Ray &normal)
{
    scene_.addEllipse(x, -y, 1, 1, calcColor(normal), brush_);
}

Geometry::Ray GraphScene::traceRay(const Geometry::Ray &ray) const
{
    Geometry::Ray nearest;
    bool wasIntersection = false;
    for (IGraphObject * obj : objects_) {
        Geometry::Ray normal;
        if (obj->intersection(ray, normal)) {
            if (!wasIntersection || Geometry::Vector(normal.getBegin(), ray.getBegin()).length2() <
                                    Geometry::Vector(nearest.getBegin(), ray.getBegin()).length2()) {
                wasIntersection = true;
                nearest = normal;
            }
        }
    }
    return nearest;
}

void GraphScene::addIlluminant(Illuminant *illuminant)
{
    illuminants.push_back(illuminant);
}
