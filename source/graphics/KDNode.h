//
// Created by ulyanin on 06.04.17.
//

#ifndef MIPT_ALGO2017_RAY_TRACING_KDNODE_H
#define MIPT_ALGO2017_RAY_TRACING_KDNODE_H


#include <vector>
#include "IGraphObject.h"

class KDNode
{
public:
    KDNode(std::vector<IGraphObject *> objects);
    void setLeft(KDNode * left);
    void setRight(KDNode * right);
    void setAxis(int axisNumber);
    bool traceRay(const Geometry::Ray &ray, Geometry::Ray &normal);
    void buildTree(const Geometry::BoundingBox &boundingBox, int depth=0);
    bool isLeaf() const;
    virtual ~KDNode();
    std::pair<Geometry::BoundingBox, Geometry::BoundingBox> chooseSplit();

protected:
    KDNode * left_;
    KDNode * right_;
    int axis_;
    std::vector<IGraphObject *> objects_;
    Geometry::BoundingBox boundingBox_;
    std::vector<IGraphObject *> sortedObjects_[3];

    static const int MAX_DEPTH = 20;
    static const int MIN_OBJECT_NUMBER = 20;

    void doSortObjects_();
};


#endif //MIPT_ALGO2017_RAY_TRACING_KDNODE_H
