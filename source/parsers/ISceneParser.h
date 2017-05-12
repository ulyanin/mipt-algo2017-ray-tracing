//
// Created by ulyanin on 12.05.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_ISCENEPARSER_H
#define MIPT_ALGO2017_RAY_TRACING_ISCENEPARSER_H

#include <string>
#include "../graphics/GraphScene.h"
#include "../graphics/GraphMaterialFactory.h"


class ISceneParser {

protected:

    GraphScene& scene_;
    GraphMaterialFactory materials_;

public:

    ISceneParser() = delete;

    ISceneParser(GraphScene &scene) :
            scene_(scene)
    {}

    virtual void openScene(const std::string &filename) = 0;

    virtual ~ISceneParser() { }
};

#endif //MIPT_ALGO2017_RAY_TRACING_ISCENEPARSER_H
