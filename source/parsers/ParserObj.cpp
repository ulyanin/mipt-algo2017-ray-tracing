//
// Created by ulyanin on 31.03.17.
//

#include "ParserObj.h"
#include "../graphics/GraphTriangle.h"
#include "../graphics/GraphQuadrangle.h"
#include <fstream>

ParserObj::ParserObj(const std::string &path) :
    path_(path)
{

}



void ParserObj::parseAll()
{
    std::ifstream in_f(path_);
    std::string word;
    bool reading_polygon = 0;
    std::vector<int> polygon;
    points_.push_back(Geometry::Point());
    while (in_f >> word) {
        if (reading_polygon && !isdigit(word[0])) {
            if (polygon.size() > 4) {
                std::cerr << "polygon size is more than 4" << std::endl;
            } else if (polygon.size() == 4) {
                objects_.push_back(new GraphQuadrangle(points_[polygon[0]],
                                                     points_[polygon[1]],
                                                     points_[polygon[2]],
                                                     points_[polygon[3]]));
            } else if (polygon.size() == 3) {
                objects_.push_back(new GraphTriangle(points_[polygon[0]],
                                                       points_[polygon[1]],
                                                       points_[polygon[2]]));
            }
        }
        if (reading_polygon && isdigit(word[0])) {
            polygon.push_back(getPointNumber(word));
        }
        else if (word == "v") {
            reading_polygon = 0;
            Geometry::Float x, y, z;
            in_f >> x >> y >> z;
            points_.emplace_back(x, y, z);
        } else if (word == "f") {
            reading_polygon = 1;
            polygon.clear();
        } else {
            reading_polygon = 0;
            std::cerr << "skip " << word << std::endl;
        }
    }
}

std::vector<IGraphObject *> ParserObj::getObjects()
{
    return objects_;
}

int ParserObj::getPointNumber(const std::string &word)
{
    size_t pos = word.find('/');
    try {
        std::stoi(word.substr(0, pos));
    } catch (std::exception &e) {
        std::cerr << "stoi '" << word << "'" << e.what() << std::endl;
    }
    return std::stoi(word.substr(0, pos));
}
