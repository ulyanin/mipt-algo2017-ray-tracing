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

GraphScene::GraphScene(const GraphScreen &screen,
                       QObject * parent, int pixelSize) :
        scene_(parent),
        view_(&scene_),
        screen_(screen),
        pixelSize_(pixelSize)
{
    scene_.setBackgroundBrush(QColor(0, 0, 0));
}

void GraphScene::addObject(IGraphObject * object)
{
    objects_.push_back(object);
}

void GraphScene::drawScene()
{
    kdTree_.setObjects(objects_);
    kdTree_.build();
    Geometry::Vector normal = screen_.getNormal();
    normal = normal.enlarge(-1);
    std::cerr << normal << std::endl;
    Geometry::Point origin(screen_.getOrigin());
    std::cerr << "origin:" << origin << std::endl;
//    view_.show();
    for (int x = 0; x < screen_.getResolutionWidth(); ++x) {
        for (int y = 0; y < screen_.getResolutionHeight(); ++y) {
            Geometry::Point curPoint(screen_.getPoint(x, y));
//            std::cout << curPoint << std::endl;
//            Geometry::Ray ray(curPoint, normal);

            // surface
            Geometry::Ray ray(origin, Geometry::Vector(origin, curPoint));
            GraphMaterial material;
            Geometry::Ray traced = traceRay(ray, material);
            GraphColor color = calcColor(traced, material);
            Geometry::Float reflect = material.getReflect();
            Geometry::Float alpha = material.getAlpha();

//            reflect = 0;

            // reflect
            Geometry::Ray ray_r(traced.reflect(ray));
//            std::cout << "!" << std::endl;
//            std::cout << traced.getDirect().dotProduct(ray_r.getDirect()) << std::endl;
//            std::cout << traced.getDirect().dotProduct(ray.getDirect()) << std::endl;
//            std::cout << "!" << std::endl;
//            std::cout <<  << std::endl;
            Geometry::Ray traced_reflect;
            GraphMaterial material_reflect;
            GraphColor color_reflect;
            if (reflect > Geometry::EPS) {
                traced_reflect = traceRay(ray_r, material_reflect);
                color_reflect = calcColor(traced_reflect, material_reflect);
            }

            // alpha
            Geometry::Ray ray_alpha(traced.getBegin() + ray.getDirect().setLength(1e-3),
                                      ray.getDirect());
            Geometry::Ray traced_alpha;
            GraphMaterial material_alpha;
            GraphColor color_alpha;
            if (1 - alpha > Geometry::EPS) {
                traced_alpha = traceRay(ray_alpha, material_alpha);
                color_alpha = calcColor(traced_alpha, material_alpha);
            }


            color = color.enlarge(1 - reflect) + color_reflect.enlarge(reflect);
            color = color.enlarge(alpha) + color_alpha.enlarge(1 - alpha);

            drawPoint(x, y, traced, color);
        }
        if (x % 10 == 0) {
            std::cerr << x << std::endl;
        }
    }
    view_.show();
}

GraphColor GraphScene::calcColor(const Geometry::Ray &normal, GraphMaterial &material) const
{
//    Geometry::Vector vectorIntensity;
    Geometry::Float intensity = 0;
    GraphMaterial tmp;
    if (!normal.getDirect().isNull()) {
        for (Illuminant *illuminant : illuminants) {
            Geometry::Ray rayDirect = illuminant->getRayTo(normal.getBegin());
            Geometry::Ray traced = traceRay(rayDirect, tmp);
            if (traced.getDirect().isNull()) {
                continue;
            }
            if (traced.getBegin() == normal.getBegin()) {
                intensity = std::max(intensity, normal.getDirect().getProjection(rayDirect.getDirect()).length2());
//                vectorIntensity += normal.getDirect().getProjection(rayDirect.getDirect());
            }
        }
    }
//    std::cout << vectorIntensity.length2() << std::endl;
//    int brightness = (int)(255 * std::min((Geometry::Float)1, vectorIntensity.length2()));
    Geometry::Float brightness = std::min((Geometry::Float)1, intensity);
    if (brightness < 0) {
        std::cerr << "wrong brightness" << std::endl;
    }
//    brightness = std::max(brightness, 0);
    brightness = Geometry::absGeomFloat(brightness);
//    return QColor(brightness, brightness, brightness);
    return material.getColor().enlarge(brightness);
}

void GraphScene::drawPoint(int x, int y, const Geometry::Ray &normal, const GraphColor &color)
{
//    scene_.addEllipse(x, -y, 1, 1, calcColor(normal), brush_);
    QColor qColor = color.toQTcolor();
    scene_.addRect(pixelSize_ * x, -pixelSize_ * y,
                   pixelSize_, pixelSize_,
                   qColor, QBrush(qColor));
}

Geometry::Ray GraphScene::traceRay(const Geometry::Ray &ray, GraphMaterial &material) const
{
    Geometry::Ray traced;
    if (!kdTree_.traceRay(ray, traced, material)) {
        traced = Geometry::Ray();
    }

    Geometry::Ray nearest;
    return traced;

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
    if (!(traced.getBegin() == nearest.getBegin())) {
        std::cerr << "traced: " << std::endl;
        std::cerr << traced.getBegin() << " " << traced.getDirect() << std::endl;
        std::cerr << "stupid:" << std::endl;
        std::cerr << nearest.getBegin() << " " << nearest.getDirect() << std::endl;
        for (IGraphObject * obj : objects_) {
            Geometry::Ray normal;
            if (obj->intersection(ray, normal) && normal.getBegin() == nearest.getBegin()) {
                std::cerr << obj << obj->getBoundingBox().getPMin() << " "<< obj->getBoundingBox().getPMax() << std::endl;
            }
        }
        kdTree_.traceRay(ray, traced, material);
    }
    return nearest;
}

void GraphScene::addIlluminant(Illuminant *illuminant)
{
    illuminants.push_back(illuminant);
}

void GraphScene::setScreen(const GraphScreen &screen)
{
    screen_ = screen;
}

void GraphScene::setResolution(int resolutionWidth, int resolutionHeight)
{
    screen_.setResolution(resolutionWidth, resolutionHeight);
}
