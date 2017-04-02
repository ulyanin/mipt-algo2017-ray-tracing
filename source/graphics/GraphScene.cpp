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
    for (int x = -100; x < width; ++x) {
        for (int y = -100; y < height; ++y) {
            Geometry::Ray ray(Geometry::Point(x, y, 0), Geometry::Vector(0, 0, 1));
            Geometry::Point nearest;
            int brightness = -1;
            for (IGraphObject * obj : objects_) {
                Geometry::Ray normal;
                if (obj->intersection(ray, normal)) {
//                    std::cout << x << " " << y << " " << normal.getDirect().dotProduct(ray.getDirect()) << std::endl;
                    if (brightness == -1 || Geometry::Vector(normal.getBegin(), ray.getBegin()).length2() <
                        Geometry::Vector(nearest, ray.getBegin()).length2()) {
                        nearest = normal.getBegin();
                        brightness = (int) (-normal.getDirect().dotProduct(ray.getDirect().norm()) * 255);
                    }
                }
            }
            if (brightness != -1) {
                QPen pen(QColor(brightness, brightness, brightness, 255));
                QBrush brush;
                scene_.addEllipse(x, y, 1, 1, pen, brush);
            }
        }
    }
    view_.show();
}
