//
// Created by ulyanin on 12.05.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_RT_FILE_H
#define MIPT_ALGO2017_RAY_TRACING_RT_FILE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "ISceneParser.h"
#include "Scanner.h"
#include "../graphics/GraphSphere.h"
#include "../graphics/GraphTriangle.h"
#include "../graphics/GraphQuadrangle.h"


using namespace Geometry;

class RT_file : public ISceneParser {

protected:
    void checkEofScanner(FileScanner &scanner, const string &group) {
        if (scanner.eof()) {
            fprintf(stderr, "Unsupported file format.\nBug with unexpected end of file in group %s", group.c_str());
            throw std::exception();
        }
    }

    virtual void parseFile(const string &filename) {
        FileScanner scanner(filename);

        string line;
        while (!scanner.eof()) {

            line = scanner.nextLine();

            if (line == "viewport") {
                viewportSection(scanner);
            } else if (line == "materials") {
                materialsSection(scanner);
            } else if (line == "lights") {
                lightsSection(scanner);
            } else if (line == "geometry") {
                geometrySection(scanner);
            } else if (line != "") {
                fprintf(stderr, "Unsupported file format.\nBug with line %s", line.c_str());
                throw std::exception();
            }
        }

        scanner.close();
    }

    virtual void viewportSection(FileScanner &scanner) {
        StringScanner stringScanner;
        string optionName;

        Vector origin, topLeft, bottomLeft, topRight;
        string line;

        while ((line = scanner.nextLine()) != "endviewport") {

            checkEofScanner(scanner, "viewport");

            stringScanner.setBuffer(line);
            optionName = stringScanner.nextString();

            if (optionName == "origin") {
                origin = stringScanner.nextVector();
            } else if (optionName == "topleft") {
                topLeft = stringScanner.nextVector();
            } else if (optionName == "bottomleft") {
                bottomLeft = stringScanner.nextVector();
            } else if (optionName == "topright") {
                topRight = stringScanner.nextVector();
            } else {
                fprintf(stderr, "Unsupported file format.\nBug with optionName %s", optionName.c_str());
                throw std::exception();
            }
        }
        scene_.setScreen(GraphScreen(origin, bottomLeft,
                                     Vector(topRight, topLeft),
                                     Vector(topLeft, bottomLeft)));
    }

    virtual void materialsSection(FileScanner &scanner) {
        string line;

        StringScanner stringScanner;
        while ((line = scanner.nextLine()) != "endmaterials") {

            checkEofScanner(scanner, "materials");

            if (line != "entry") {
                fprintf(stderr, "Unsupported file format.\nBug with entry %s", line.c_str());
                throw std::exception();
            }
            readMaterialEntry(scanner);
        }
    }

    void readMaterialEntry(FileScanner &scanner) {
        string line;

        string material_name;
        GraphColor color;
        Float alpha = 0, reflect = 0, refract = 0;

        StringScanner stringScanner;
        string optionName;

        while ((line = scanner.nextLine()) != "endentry") {

            checkEofScanner(scanner, "materials -> entry");

            stringScanner.setBuffer(line);
            optionName = stringScanner.nextString();

            if (optionName == "name") {
                material_name = stringScanner.nextString();
            } else if (optionName == "alpha") {
                alpha = stringScanner.nextDouble();
            } else if (optionName == "reflect") {
                reflect = stringScanner.nextDouble();
            } else if (optionName == "refract") {
                refract = stringScanner.nextDouble();
            } else if (optionName == "color") {
                int r, g, b;
                r = stringScanner.nextInt();
                g = stringScanner.nextInt();
                b = stringScanner.nextInt();
                color = GraphColor(r, g, b);
            } else {
                fprintf(stderr, "Unsupported file format.\nBug with materials -> entry -> optionName %s",
                        optionName.c_str());
                throw std::exception();
            }
        }
        materials_.addMaterial(new GraphMaterial(material_name,
                                                 color,
                                                 alpha,
                                                 reflect,
                                                 refract));
    }

    void lightsSection(FileScanner &scanner) {
        string line;

        StringScanner stringScanner;
        while ((line = scanner.nextLine()) != "endlights") {
            if (scanner.eof()) {
                fprintf(stderr, "Unsupported file format.\nBug with endlights %s", line.c_str());
                throw std::exception();
            }

            if (line != "reference") {
                fprintf(stderr, "Unsupported file format.\nBug with entry %s", line.c_str());
                throw std::exception();
            }

            readReferenceAndLightEntry(scanner);

        }
    }

    void readReferenceAndLightEntry(FileScanner &scanner) {
        string line, optionName;

        StringScanner stringScanner;

        Float power = 0, distance = 0;

        while ((line = scanner.nextLine()) != "endreference") {


            checkEofScanner(scanner, "lights -> reference");

            stringScanner.setBuffer(line);

            optionName = stringScanner.nextString();

            if (optionName == "power") {
                power = stringScanner.nextDouble();
            } else if (optionName == "distance") {
                distance = stringScanner.nextDouble();
            } else {
                fprintf(stderr, "Unsupported file format.\nBug with lights -> entry -> optionName %s",
                        optionName.c_str());
                throw std::exception();
            }
        }


        Float scaleFactor = Geometry::sqr(distance) / power;

        Vector position;
        power = 0;

        line = scanner.nextLine();
        if (line != "point") {
            fprintf(stderr, "Unsupported file format.\nBug with lights -> entry -> point %s", optionName.c_str());
            throw std::exception();
        }
        while ((line = scanner.nextLine()) != "endpoint") {

            checkEofScanner(scanner, "lights -> point");

            stringScanner.setBuffer(line);

            optionName = stringScanner.nextString();

            if (optionName == "coords") {
                position = stringScanner.nextVector();
            } else if (optionName == "power") {
                power = stringScanner.nextDouble();
            } else {
                fprintf(stderr, "Unsupported file format.\nBug with lights -> entry -> optionName %s",
                        optionName.c_str());
                throw std::exception();
            }
        }
        scene_.addIlluminant(new Illuminant(position, scaleFactor * power));
    }

    void geometrySection(FileScanner &scanner) {
        string line;
        StringScanner stringScanner;
        string optionName;

        while ((line = scanner.nextLine()) != "endgeometry") {

            checkEofScanner(scanner, "geometry");

            stringScanner.setBuffer(line);

            optionName = stringScanner.nextString();

            if (optionName == "sphere") {
                readSphere(scanner);
            } else if (optionName == "triangle") {
                readTriangle(scanner);
            } else if (optionName == "quadrangle") {
                readQuadrangle(scanner);
            } else {
                fprintf(stderr, "Unsupported file format.\nBug with entry %s", line.c_str());
                throw std::exception();
            }
        }
    }

    void readSphere(FileScanner &scanner) {
        string line;

        string material_name;
        Point position;
        Float radius = 0;

        StringScanner stringScanner;
        string optionName;

        while ((line = scanner.nextLine()) != "endsphere") {

            checkEofScanner(scanner, "geometry -> sphere");

            stringScanner.setBuffer(line);
            optionName = stringScanner.nextString();

            if (optionName == "material") {
                material_name = stringScanner.nextString();
            } else if (optionName == "radius") {
                radius = stringScanner.nextDouble();
            } else if (optionName == "coords") {
                position = stringScanner.nextVector();
            } else {
                fprintf(stderr, "Unsupported file format.\nBug with materials -> entry -> %s", optionName.c_str());
                throw std::exception();
            }
        }
        scene_.addObject(new GraphSphere(position,
                                         radius,
                                         *materials_.getMaterial(material_name)));

    }

    void readTriangle(FileScanner &scanner) {
        string line;

        string material_name;

        StringScanner stringScanner;
        string optionName;

        std::vector<Point> vertexes;

        while ((line = scanner.nextLine()) != "endtriangle") {

            checkEofScanner(scanner, "geometry -> triangle");

            stringScanner.setBuffer(line);
            optionName = stringScanner.nextString();

            if (optionName == "vertex") {
                vertexes.push_back(stringScanner.nextVector());
            } else if (optionName == "material") {
                material_name = stringScanner.nextString();
            } else {
                fprintf(stderr, "Unsupported file format.\nBug with materials -> entry -> %s", optionName.c_str());
                throw std::exception();
            }
        }

        if (vertexes.size() != 3) {
            fprintf(stderr, "Unsupported file format.\nBug with sphere vertex count -> %lu", vertexes.size());
            throw std::exception();
        }

        scene_.addObject(new GraphTriangle(vertexes[0], vertexes[1], vertexes[2],
                                           *materials_.getMaterial(material_name)));
    }

    void readQuadrangle(FileScanner &scanner) {
        string line;

        string material_name;

        StringScanner stringScanner;
        string optionName;

        std::vector<Point> vertexes;

        while ((line = scanner.nextLine()) != "endquadrangle") {

            checkEofScanner(scanner, "geometry -> quadrangle");

            stringScanner.setBuffer(line);
            optionName = stringScanner.nextString();

            if (optionName == "vertex") {
                vertexes.push_back(stringScanner.nextVector());
            } else if (optionName == "material") {
                material_name = stringScanner.nextString();
            } else {
                fprintf(stderr, "Unsupported file format.\nBug with materials -> entry -> %s", optionName.c_str());
                throw std::exception();
            }
        }

        if (vertexes.size() != 4) {
            fprintf(stderr, "Unsupported file format.\nBug with sphere vertex count -> %lu", vertexes.size());
            throw std::exception();
        }

        scene_.addObject(new GraphQuadrangle(vertexes[0], vertexes[1], vertexes[2], vertexes[3],
                                             *materials_.getMaterial(material_name)));

    }


public:
    RT_file() = delete;

    RT_file(GraphScene &scene)
            : ISceneParser(scene) {}

    void openScene(const string &filename, const string &directory) override {
        parseFile(directory + filename);
    }

};

#endif //MIPT_ALGO2017_RAY_TRACING_RT_FILE_H
