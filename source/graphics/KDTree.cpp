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
    for (IGraphObject * object : objects_) {
        if (!boundingBox_.isInside(object->getBoundingBox().getPMin())) {
            throw std::runtime_error("whole bounding box does not contain all (min)");
        }
        if (!boundingBox_.isInside(object->getBoundingBox().getPMax())) {
            throw std::runtime_error("whole bounding box does not contain all (min)");
        }
    }
    root_ = new KDNode(objects_);
    root_->buildTree(boundingBox_);
}

bool KDTree::traceRay(const Geometry::Ray &ray, Geometry::Ray &normal) const
{
    return root_->traceRay(ray, normal);
}

void KDTree::setObjects(std::vector<IGraphObject *> objects)
{
    objects_ = objects;
}

//void KDTree::buildBox_(KDNode * &node, std::vector<IGraphObject *> objects,
//                       const Geometry::BoundingBox &boundingBox)
//{
//    std::vector<IGraphObject *> sortedObjects[3];
//    int bestAxis = 0;
//    Geometry::BoundingBox leftBox, rightBox;
//    Geometry::Float minFunc = -1;
//    for (int axis = 0; axis < 3; ++axis) {
//        sortedObjects[axis] = objects;
//        std::sort(sortedObjects[axis].begin(),
//                  sortedObjects[axis].end(),
//                  [axis] (IGraphObject * A, IGraphObject * B) -> bool {
//                      return A->getMinimumAlongAxis(axis) <
//                             B->getMinimumAlongAxis(axis);
//                  }
//        );
//        for (size_t leftNumber = 0; leftNumber < sortedObjects[axis].size(); ++leftNumber) {
//            size_t rightNumber = sortedObjects[axis].size() - leftNumber;
//            auto boxPair = boundingBox.split(
//                    axis,
//                    sortedObjects[axis][leftNumber]->getMinimumAlongAxis(axis) - Geometry::EPS);
//            Geometry::Float leftFunc = leftNumber * boxPair.first.getSurfaceArea();
//            Geometry::Float rightFunc = rightNumber * boxPair.second.getSurfaceArea();
//            if (minFunc < 0 || leftFunc + rightFunc < minFunc) {
//                minFunc = leftFunc + rightFunc;
//                bestAxis = axis;
//                leftBox = boxPair.first;
//                rightBox = boxPair.second;
//            }
//        }
//    }
//    std::vector<IGraphObject *> leftList;
//    std::vector<IGraphObject *> rightList;
//    for (IGraphObject * objectPtr : sortedObjects[bestAxis]) {
//        if (objectPtr->insideABox(leftBox)) {
//            leftList.push_back(objectPtr);
//        }
//        if (objectPtr->insideABox(rightBox)) {
//            rightList.push_back(objectPtr);
//        }
//    }
//    node->setLeft(new KDNode(leftList));
//    node->setRight(new KDNode(rightList));
//    buildBox_();
//}
