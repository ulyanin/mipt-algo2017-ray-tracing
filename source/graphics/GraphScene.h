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

class GraphScene
{
public:
    GraphScene(QObject * parent = Q_NULLPTR);
    void addObject(IGraphObject * object);
    void addIlluminant(Illuminant * illuminant);
    Geometry::Ray traceRay(const Geometry::Ray &ray) const;
    void drawScene();
    QColor calcColor(const Geometry::Ray &normal) const;
    void drawPoint(int x, int y, const Geometry::Ray &normal);
protected:
    QGraphicsScene scene_;
    QGraphicsView view_;
    QBrush brush_;
    std::vector<IGraphObject *> objects_;
    std::vector<Illuminant *> illuminants;
};


#endif //MIPT_ALGO2017_RAY_TRACING_GRAPHSCENE_H
