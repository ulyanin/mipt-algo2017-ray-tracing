//
// Created by ulyanin on 31.03.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_PARSEROBJ_H
#define MIPT_ALGO2017_RAY_TRACING_PARSEROBJ_H


#include "../graphics/IGraphObject.h"
#include "../geometry/Point.h"
#include <vector>
#include <string>

class ParserObj
{
public:
    ParserObj(const std::string &path);

    void parseAll();

    std::vector<IGraphObject *> getObjects();

protected:
    std::string path_;
    std::vector<IGraphObject *> objects_;
    std::vector<Geometry::Point> points_;

    static int getPointNumber(const std::string &word);
};


#endif //MIPT_ALGO2017_RAY_TRACING_PARSEROBJ_H
