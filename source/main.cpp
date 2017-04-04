/*
 * @author ulyanin
 */

#include <iostream>
#include <QApplication>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <chrono>
#include "geometry/Vector.h"
#include "geometry/Sphere.h"
#include "graphics/GraphScene.h"
#include "graphics/GraphSphere.h"
#include "graphics/GraphTriangle.h"
#include "graphics/GraphQuadrangle.h"

int main(int argv, char **args)
{

    auto start = std::chrono::system_clock::now();
    QApplication app(argv, args);

    GraphScene scene(&app);
    int t1 = 100;
    int w = 800;
    int dist = 500;
    int dist_ill = 100;
    Geometry::Point A(t1, t1, dist);
    Geometry::Point B(w - t1, t1, dist);
    Geometry::Point C(w - t1, w - t1, dist);
    Geometry::Point D(t1, w - t1, dist);
    scene.addIlluminant(new Illuminant(Geometry::Point(0, 0, -dist_ill)));
    scene.addIlluminant(new Illuminant(Geometry::Point(0, w, -dist_ill)));
    scene.addIlluminant(new Illuminant(Geometry::Point(w, w, -dist_ill)));
    scene.addIlluminant(new Illuminant(Geometry::Point(w, 0, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(0, 0, -100)));

//    scene.addObject(new GraphSphere(A, 100));
//    scene.addObject(new GraphSphere(B, 90));
//    scene.addObject(new GraphSphere(C, 80));
//    scene.addObject(new GraphSphere(D, 70));
    scene.addObject(new GraphSphere(Geometry::Point(w/2, w/2, dist - 100), 100));
//    scene.addObject(new GraphTriangle(A, B, C));
    scene.addObject(new GraphQuadrangle(A, B, C, D));
    scene.drawScene();
    /*
     *
    GraphScene scene(&app);
    Geometry::Point A(0, 0, 600);
    Geometry::Point B(600, 0, 600);
    Geometry::Point C(600, 600, 600);
    scene.addObject(new GraphSphere(A, 100));
    scene.addObject(new GraphSphere(B, 100));
    scene.addObject(new GraphSphere(C, 100));
//    scene.addObject(new GraphSphere(D, 100));
    scene.addObject(new GraphTriangle(A, B, C));
     */

    /*
    QGraphicsScene scene(&app);
    QGraphicsView view(&scene);

// a white semi-transparent foreground
    scene.setBackgroundBrush(QColor(0, 0, 0));
//    scene.setForegroundBrush(QColor(0, 0, 0, 255));

    QPen pen[2] = {QPen(QColor(255, 0, 0, 255)), QPen(QColor(0, 0, 255, 255))};
    QBrush brush(QColor(0, 255, 0));
//    view.resize(100, 100);
    for (int i = 0; i < 100; ++i) {
        for (int j = i; j < 100; ++j) {
            scene.addEllipse(i, j, 1, 1, pen[i + j & 1], brush);
        }
    }
//    view.resize(200, 200);
    view.show();


// a grid foreground
//    scene.setForegroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
*/

    auto end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration<double>(end - start).count() << std::endl;
    return app.exec();
}
