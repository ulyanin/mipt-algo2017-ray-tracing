//
// Created by ulyanin on 31.03.17.
//

#include "parserObj.h"
#include <fstream>

parserObj::parserObj(const std::string &path) :
    path_(path)
{

}

void parserObj::parseAll()
{
    std::ifstream in_f(path_);
    std::string word;
    bool reading_polygon = 0;
    std::vector<int> polygon;
    while (in_f >> word) {
        if (reading_polygon && !isdigit(word[0])) {
            if (polygon.size() > 4) {

            } else if (polygon.size() == 4) {

            } else if (polygon.size() == 3) {

            }
        }
        if (reading_polygon) {
            polygon.push_back(getPointNumber(word));
        }
        else if (word == "v") {
            reading_polygon = 0;
        } else if (word == "f") {
            reading_polygon = 1;
            polygon.clear();
        }
    }
}

std::vector<IGraphObject *> parserObj::getObjects()
{
    return std::vector<IGraphObject *>();
}

int parserObj::getPointNumber(const std::string &word)
{
    size_t pos = word.find('/');
    return std::stoi(word.substr(0, pos));
}
