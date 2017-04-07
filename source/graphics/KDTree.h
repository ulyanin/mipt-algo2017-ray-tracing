//
// Created by ulyanin on 06.04.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_KDTREE_H
#define MIPT_ALGO2017_RAY_TRACING_KDTREE_H


#include "KDNode.h"
#include "IGraphObject.h"
#include "../geometry/BoundingBox.h"

class KDTree
{
public:
    KDTree();

    KDTree(std::vector<IGraphObject *> objects);

    void setObjects(std::vector<IGraphObject *> objects);

    virtual ~KDTree();

    void build();

    bool traceRay(const Geometry::Ray &ray, Geometry::Ray &normal) const;

protected:
//    void buildBox_(KDNode * &node,
//                   std::vector<IGraphObject *> objects,
//                   const Geometry::BoundingBox &boundingBox);

    KDNode * root_;
    std::vector<IGraphObject *> objects_;
    Geometry::BoundingBox boundingBox_;
};



#endif //MIPT_ALGO2017_RAY_TRACING_KDTREE_H
