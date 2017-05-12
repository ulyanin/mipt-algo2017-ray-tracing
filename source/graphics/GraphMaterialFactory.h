//
// Created by ulyanin on 12.05.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_GRAPHMATERIALFACTORY_H
#define MIPT_ALGO2017_RAY_TRACING_GRAPHMATERIALFACTORY_H

#include <vector>
#include "GraphMaterial.h"

class GraphMaterialFactory
{
public:
    GraphMaterialFactory();
    virtual ~GraphMaterialFactory();
    void addMaterial(GraphMaterial * material);
    GraphMaterial * getMaterial(const std::string &materialName);
    GraphMaterial * getMaterial(int materialId);
protected:
    std::vector<GraphMaterial *> materials_;
};


#endif //MIPT_ALGO2017_RAY_TRACING_GRAPHMATERIALFACTORY_H
