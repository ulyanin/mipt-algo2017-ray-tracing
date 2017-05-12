//
// Created by ulyanin on 13.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_GRAPHSCENE_H
#define MIPT_ALGO2017_RAY_TRACING_GRAPHSCENE_H

#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include "../geometry/GeomFloat.h"
#include <vector>
#include "IGraphObject.h"
#include "Illuminant.h"
#include "../geometry/Quadrangle.h"
#include "GraphScreen.h"
#include "KDTree.h"

class GraphScene
{
public:
    GraphScene(QObject * parent = Q_NULLPTR);
    GraphScene(const GraphScreen &screen,
               QObject * parent = Q_NULLPTR, int pixelSize=2);
//    GraphScene(GraphScene &&movable) noexcept;
    void addObject(IGraphObject * object);
    void addIlluminant(Illuminant * illuminant);
    Geometry::Ray traceRay(const Geometry::Ray &ray, GraphMaterial &material) const;
    void drawScene();
    GraphColor calcColor(const Geometry::Ray &normal, GraphMaterial &material) const;
    void drawPoint(int x, int y, const Geometry::Ray &normal, const GraphColor &color);
    void setScreen(const GraphScreen &screen);
    void setResolution(int resolutionWidth, int resolutionHeight);
protected:
    QGraphicsScene scene_;
    QGraphicsView view_;
    QBrush brush_;
    int width_, height_;
    GraphScreen screen_;
    int pixelSize_ = 2;
    KDTree kdTree_;
    std::vector<IGraphObject *> objects_;
    std::vector<Illuminant *> illuminants;
};


#endif //MIPT_ALGO2017_RAY_TRACING_GRAPHSCENE_H
