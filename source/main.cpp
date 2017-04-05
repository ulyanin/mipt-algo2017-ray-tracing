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
#include "parsers/ParserObj.h"



inline void draw_test(QApplication * appPtr)
{
    GraphScene scene(GraphScreen(
            Geometry::Point(-5, -5, 0),
            Geometry::Vector(0, 500, 0),
            Geometry::Vector(500, 0, 0),
            50, 50),
                     appPtr);
    int t1 = 100;
    int w = 500;
    int dist = 500;
    int dist_ill = 100;
    Geometry::Point A(t1, t1, dist);
    Geometry::Point B(w - t1, t1, dist);
    Geometry::Point C(w - t1, w - t1, dist);
    Geometry::Point D(t1, w - t1, dist);
    scene.addIlluminant(new Illuminant(Geometry::Point(0, 0, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(0, w, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(w, w, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(w, 0, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(0, 0, -100)));

//    scene.addObject(new GraphSphere(A, 100));
//    scene.addObject(new GraphSphere(B, 90));
//    scene.addObject(new GraphSphere(C, 80));
//    scene.addObject(new GraphSphere(D, 70));
    scene.addObject(new GraphSphere(Geometry::Point(w/2, w/2, dist - 100), 100));
//    scene.addObject(new GraphTriangle(A, B, C));
    scene.addObject(new GraphQuadrangle(A, B, C, D));
    scene.drawScene();
}

inline GraphScreen screenFemale()
{
    return GraphScreen(
            Geometry::Point(5, 3.5, 0.5),
            Geometry::Vector(0, 0, -1).setLength(1),
            Geometry::Vector(0, 1, 0).setLength(1),
            90, 90);
}

inline GraphScreen screenTree()
{
    return GraphScreen(
            Geometry::Point(-5, -5, 10),
            Geometry::Vector(1, 0, 0).setLength(10),
            Geometry::Vector(0, 1, 0).setLength(10),
            800, 800);
}

inline GraphScreen screenWolf()
{
    return GraphScreen(
            Geometry::Point(-60, -30, 200),
            Geometry::Vector(1, 0, 0).setLength(150),
            Geometry::Vector(0, 1, 0).setLength(300),
            90, 2 * 90);
}
inline GraphScreen screenWolf2()
{
    return GraphScreen(
            Geometry::Point(-100, -30, 100) + Geometry::Vector(-1, 0, -1).setLength(150),
            Geometry::Vector(1, 0, 1).setLength(400),
            Geometry::Vector(0, 1, 0).setLength(300),
            90 * 4 / 3 * 10, 90 * 10);
}

int main(int argv, char **args)
{

    auto start = std::chrono::system_clock::now();
    QApplication app(argv, args);
    GraphScene scene(screenWolf2(),
                     &app,
                     1);
//    GraphScene scene(GraphScreen(
//            Geometry::Point(-0.5, 3.5, 5),
//            Geometry::Vector(1, 0, 0).enlarge(1),
//            Geometry::Vector(0, 1, 0).enlarge(1),
//            30 * 30, 30 * 30),
//                     &app);
    int t1 = 1;
    int w = 4;
    int dist = 20;
    int dist_ill = 10;
    Geometry::Point A(-w, -w, -dist);
    Geometry::Point B(w, -w, -dist);
    Geometry::Point C(w, w, -dist);
    Geometry::Point D(-w, w, -dist);
//    scene.addIlluminant(new Illuminant(Geometry::Point(-dist_ill/2, 0, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(-60, 0, 50)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(60, 0, 50)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(60, 0, 0)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(0, 0, 200)));
    scene.addIlluminant(new Illuminant(Geometry::Point(-200, 200, -300), 1000 * 100.0));
    scene.addIlluminant(new Illuminant(Geometry::Point(0, 200, 300), 1000 * 70.0));
//    scene.addIlluminant(new Illuminant(Geometry::Point(0, 10, -0.5)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(0, w, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(w, w, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(w, 0, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(0, 0, -100)));

//    scene.addObject(new GraphSphere(A, 0.1));
//    scene.addObject(new GraphSphere(Geometry::Point(0, 0, -25), 1));
//    scene.addObject(new GraphSphere(B, 0.09));
//    scene.addObject(new GraphSphere(C, 0.08));
//    scene.addObject(new GraphSphere(D, 0.07));
//    scene.addObject(new GraphSphere(Geometry::Point(w/2, w/2, dist - 0.5), 0.5));
//    scene.addObject(new GraphTriangle(A, B, C));
//    scene.addObject(new GraphQuadrangle(A, B, C, D));
//    scene.drawScene();



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
    ParserObj parser("./models/Wolf.obj");
    parser.parseAll();
    std::vector<IGraphObject *> objects = parser.getObjects();
    std::cerr << objects.size() << std::endl;
    for (IGraphObject * obj : objects) {
        scene.addObject(obj);
    }
//    scene.addObject(new GraphQuadrangle(
//            Geometry::Point(0, 0, 0),
//            Geometry::Point(1, 0, 0),
//            Geometry::Point(1, 1, 0),
//            Geometry::Point(0, 1, 0)
//    ));
    auto end = std::chrono::system_clock::now();
    std::cerr << std::chrono::duration<double>(end - start).count() << std::endl;
    scene.drawScene();
    end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration<double>(end - start).count() << std::endl;
    return app.exec();
}
