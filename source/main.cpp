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
#include "graphics/KDTree.h"


inline GraphScreen screenFemale()
{
    return GraphScreen(
            Geometry::Point(5, 3.5, 0.5),
            Geometry::Vector(0, 0, -1).setLength(1),
            Geometry::Vector(0, 1, 0).setLength(1),
            800, 800);
}
inline GraphScreen screenDog()
{
    return GraphScreen(
            Geometry::Point(2.1, -0.5, 4),
            Geometry::Vector(1, 0, -1).setLength(5),
            Geometry::Vector(0, 1, 0).setLength(4),
            50 * 5 * 5, 50 * 5 * 4);
}


inline GraphScreen screenTree()
{
    return GraphScreen(
            Geometry::Point(-5, -5, 10),
            Geometry::Vector(1, 0, 0).setLength(10),
            Geometry::Vector(0, 1, 0).setLength(10),
            80 * 10, 80 * 10);
}

inline GraphScreen screenWolf()
{
    return GraphScreen(
            Geometry::Point(-60, -30, 200),
            Geometry::Vector(1, 0, 0).setLength(150),
            Geometry::Vector(0, 1, 0).setLength(300),
            90 * 5, 2 * 90 * 5);
}
inline GraphScreen screenWolf2()
{
    return GraphScreen(
            Geometry::Point(-100, -30, 100) + Geometry::Vector(-1, 0, -1).setLength(150),
            Geometry::Vector(1, 0, 1).setLength(400),
            Geometry::Vector(0, 1, 0).setLength(300),
            90 * 4 / 3 * 5, 90 * 5);
}

int main(int argv, char **args)
{

    auto start = std::chrono::system_clock::now();
    QApplication app(argv, args);
    GraphScene scene(screenFemale(),
                     &app,
                     1);
//    GraphScene scene(GraphScreen(
//            Geometry::Point(0, 0, 5),
//            Geometry::Vector(1, 0, 0).enlarge(70),
//            Geometry::Vector(0, 1, 0).enlarge(70),
//            30 * 5, 30 * 5),
//                     &app, 3);
    int t1 = 1;
    int w = 50;
    int dist = 20;
    int dist_ill = 10;
    Geometry::Point A(0, 0, -dist);
    Geometry::Point B(w, 0, -dist);
    Geometry::Point C(w, w, -dist);
    Geometry::Point D(0, w, -dist);
//    scene.addIlluminant(new Illuminant(Geometry::Point(-dist_ill/2, 0, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(-60, 0, 50)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(60, 0, 50)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(60, 0, 0)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(0, 0, 200)));\

//    scene.addIlluminant(new Illuminant(Geometry::Point(-200, 200, -300), 1000 * 100.0));
//    scene.addIlluminant(new Illuminant(Geometry::Point(0, 200, 300), 1000 * 70.0));

//    scene.addIlluminant(new Illuminant(Geometry::Point(5, 100, 10)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(100, 100, 10)));
    scene.addIlluminant(new Illuminant(Geometry::Point(-20, 2, 20), 800));
//    scene.addIlluminant(new Illuminant(Geometry::Point(-10, 2, -10)));
    scene.addIlluminant(new Illuminant(Geometry::Point(20, 2, -20), 800));
//    scene.addIlluminant(new Illuminant(Geometry::Point(10, 2, 10)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(0, w, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(w, w, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(w, 0, -dist_ill)));
//    scene.addIlluminant(new Illuminant(Geometry::Point(100, 300, 0)));


    ParserObj parser(args[1]);
    parser.parseAll();
    std::vector<IGraphObject *> objects = parser.getObjects();
    std::cerr << objects.size() << std::endl;
    for (IGraphObject * obj : objects) {
        scene.addObject(obj);
    }
//    scene.addObject(new GraphQuadrangle(A, B, C, D));
    auto end = std::chrono::system_clock::now();
    std::cerr << std::chrono::duration<double>(end - start).count() << std::endl;
    scene.drawScene();
//    KDTree kdTree(objects);
//    kdTree.build();
//    Geometry::Ray normal;
//    std::cout << "begin test" << std::endl;
//    std::cout << kdTree.traceRay(Geometry::Ray(Geometry::Point(1.5, 0.5, 0.5), Geometry::Vector(-1, 0, 0)), normal) << std::endl;
//    std::cout << normal.getBegin() << std::endl;
//    std::cout << normal.getDirect() << std::endl;
//    std::cout << "end test" << std::endl;
    end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration<double>(end - start).count() << std::endl;
    return app.exec();
}
