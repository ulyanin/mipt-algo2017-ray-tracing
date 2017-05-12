//
// Created by ulyanin on 15.04.17.
//
#ifndef MIPT_ALGO2017_RAY_TRACING_PARSERT_H
#define MIPT_ALGO2017_RAY_TRACING_PARSERT_H


#include "../graphics/IGraphObject.h"


class ParserRT
{
public:
    ParserRT(const std::string &path);

    void parseAll();

    std::vector<IGraphObject *> getObjects();

protected:
    std::string path_;
    std::vector<IGraphObject *> objects_;
    std::vector<Geometry::Point> points_;

};


#endif //MIPT_ALGO2017_RAY_TRACING_PARSERT_H
