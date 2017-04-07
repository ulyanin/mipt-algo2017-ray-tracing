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
//    view_.setStyleSheet("background-color: transparent;");
//    view_.setBackgroundBrush(QColor(0, 0, 100, 200));
}

GraphScene::GraphScene(const GraphScreen &screen,
                       QObject * parent, int pixelSize) :
        scene_(parent),
        view_(&scene_),
        screen_(screen),
        pixelSize_(pixelSize),
        kdTree_(objects_)
{
    scene_.setBackgroundBrush(QColor(0, 0, 0));
}

void GraphScene::addObject(IGraphObject * object)
{
    objects_.push_back(object);
}

void GraphScene::drawScene()
{
    Geometry::Vector normal = screen_.getNormal();
    std::cerr << normal << std::endl;
//    view_.show();
    for (int x = 0; x < screen_.getResolutionWidth(); ++x) {
        for (int y = 0; y < screen_.getResolutionHeight(); ++y) {
            Geometry::Ray ray(screen_.getPoint(x, y), normal);
            drawPoint(x, y, traceRay(ray));
        }
        if (x % 10 == 0) {
            std::cerr << x << std::endl;
        }
    }
    view_.show();
}

QColor GraphScene::calcColor(const Geometry::Ray &normal) const
{
    Geometry::Vector vectorIntensity;
    if (!normal.getDirect().isNull()) {
        for (Illuminant *illuminant : illuminants) {
            Geometry::Ray rayDirect = illuminant->getRayTo(normal.getBegin());
            Geometry::Ray traced = traceRay(rayDirect);
            if (traced.getDirect().isNull()) {
                continue;
            }
            if (traced.getBegin() == normal.getBegin()) {
                vectorIntensity += normal.getDirect().getProjection(rayDirect.getDirect());
            }
        }
    }
//    std::cout << vectorIntensity.length2() << std::endl;
    int brightness = (int)(255 * std::min((Geometry::Float)1, vectorIntensity.length2()));
    if (brightness < 0) {
        std::cerr << "wrong brightness" << std::endl;
    }
//    brightness = std::max(brightness, 0);
    brightness = abs(brightness);
    return QColor(brightness, brightness, brightness);
}

void GraphScene::drawPoint(int x, int y, const Geometry::Ray &normal)
{
//    scene_.addEllipse(x, -y, 1, 1, calcColor(normal), brush_);
    QColor color = std::move(calcColor(normal));
    scene_.addRect(pixelSize_ * x, -pixelSize_ * y,
                   pixelSize_, pixelSize_,
                   color, QBrush(color));
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
