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

int main(int argv, char **args)
{
    auto start = std::chrono::system_clock::now();
    QApplication app(argv, args);
    GraphScene scene(&app);
    Geometry::Point A(0, 600, 600);
    Geometry::Point B(600, 0, 600);
    Geometry::Point C(0, 0, 600);
    scene.addObject(new GraphSphere(A, 100));
    scene.addObject(new GraphSphere(B, 100));
    scene.addObject(new GraphSphere(C, 100));
    scene.addObject(new GraphTriangle(A, B, C));
    scene.drawScene();
/*
    QGraphicsScene scene(&app);
    QGraphicsView view(&scene);

// a white semi-transparent foreground
    scene.setBackgroundBrush(QColor(0, 0, 0));
//    scene.setForegroundBrush(QColor(0, 0, 0, 255));

    QPen pen[2] = {QPen(QColor(255, 0, 0, 255)), QPen(QColor(0, 0, 255, 255))};
    QBrush brush(QColor(0, 255, 0));
//    view.resize(100, 100);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            scene.addEllipse(i, j, 1, 1, pen[i + j & 1], brush);
        }
    }
//    view.resize(200, 200);
    view.show();
// a grid foreground
//    scene.setForegroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));

    auto end = std::chrono::system_clock::now();

    std::cout << std::chrono::duration<double>(end - start).count() << std::endl;
//    std::cout << std::chrono::duration<double, std::ratio<60, 1> >(end - start).count() << std::endl;

    Geometry::Point a(1, 1, 1);
    Geometry::Vector v(2, 2, 2);
    Geometry::Sphere s(a, 1);
    std::cout << a << " " << v << " " << (Geometry::Vector(a) + v) << std::endl;
*/
    auto end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration<double>(end - start).count() << std::endl;
    return app.exec();
}
