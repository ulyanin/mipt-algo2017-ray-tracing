//
// Created by ulyanin on 12.05.17.
//

#include "GraphMaterialFactory.h"


GraphMaterialFactory::GraphMaterialFactory()
{

}

GraphMaterialFactory::~GraphMaterialFactory()
{
    for (auto materialPtr : materials_) {
        delete materialPtr;
    }
}

void GraphMaterialFactory::addMaterial(GraphMaterial *material)
{
    materials_.push_back(material);
}

GraphMaterial *GraphMaterialFactory::getMaterial(const std::string &materialName)
{
    for (auto materialPtr : materials_) {
        if (materialPtr->getName() == materialName) {
            return materialPtr;
        }
    }
    return nullptr;
}
