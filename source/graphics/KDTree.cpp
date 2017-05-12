#include "KDTree.h"

KDTree::KDTree()
{

}

KDTree::~KDTree()
{
    delete root_;
}

KDTree::KDTree(std::vector<IGraphObject *> objects) :
        objects_(objects)
{

}

void KDTree::build()
{
    /*
     * preparing data
     */
    Geometry::Point minPoint, maxPoint;
    if (!objects_.empty()) {
        minPoint = objects_.front()->getBoundingBox().getPMin();
        maxPoint = objects_.front()->getBoundingBox().getPMax();
    }
    for (IGraphObject * object : objects_) {
        for (int axis = 0; axis < 3; ++axis) {
            minPoint.setAxis(axis,
                             std::min(minPoint.getAxisCoordinate(axis),
                                      object->getMinimumAlongAxis(axis)));
            maxPoint.setAxis(axis,
                             std::max(maxPoint.getAxisCoordinate(axis),
                                      object->getMaximumAlongAxis(axis)));
        }
    }
    boundingBox_ = Geometry::BoundingBox(minPoint, maxPoint);
//    /for (IGraphObject * object : objects_) {
//        if (!boundingBox_.isInside(object->getBoundingBox().getPMin())) {
//            throw std::runtime_error("whole bounding box does not contain all (min)");
//        }
//        if (!boundingBox_.isInside(object->getBoundingBox().getPMax())) {
//            throw std::runtime_error("whole bounding box does not contain all (min)");
//        }
//    }
    root_ = new KDNode(objects_);
    root_->buildTree(boundingBox_);
}

bool KDTree::traceRay(const Geometry::Ray &ray, Geometry::Ray &normal, GraphMaterial &material) const
{
    return root_->traceRay(ray, normal, material);
}

void KDTree::setObjects(std::vector<IGraphObject *> objects)
{
    objects_ = objects;
}

