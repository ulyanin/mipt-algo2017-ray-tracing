//
// Created by ulyanin on 06.04.17.
//

#include "KDNode.h"

KDNode::KDNode(std::vector<IGraphObject *> objects) :
        left_(nullptr),
        right_(nullptr),
        objects_(objects)
{
}


void KDNode::setLeft(KDNode *left)
{
    left_ = left;
}


void KDNode::setRight(KDNode *right)
{
    right_ = right;
}

void KDNode::setAxis(int axisNumber)
{
    axis_ = axisNumber;
}



void KDNode::buildTree(const Geometry::BoundingBox &boundingBox, int depth)
{
    boundingBox_ = boundingBox;

    doSortObjects_();

    if (objects_.size() <= MIN_OBJECT_NUMBER || depth >= MAX_DEPTH) {
        return;
    }

    auto pairBox = chooseSplit();

    std::vector<IGraphObject *> leftList;
    std::vector<IGraphObject *> rightList;
    for (IGraphObject * objectPtr : objects_) {
        if (objectPtr->insideABox(pairBox.first)) {
            leftList.push_back(objectPtr);
        }
        if (objectPtr->insideABox(pairBox.second)) {
            rightList.push_back(objectPtr);
        }
    }
    left_ = new KDNode(leftList);
    right_ = new KDNode(rightList);
    left_->buildTree(pairBox.first, depth + 1);
    right_->buildTree(pairBox.second, depth + 1);

}


std::pair<Geometry::BoundingBox, Geometry::BoundingBox> KDNode::chooseSplit()
{
    int bestAxis = 0;
    Geometry::BoundingBox leftBox, rightBox;
    Geometry::Float minFunc = -1;
    for (int axis = 0; axis < 3; ++axis) {
        for (size_t leftNumber = 0; leftNumber < sortedObjects_[axis].size(); ++leftNumber) {
            size_t rightNumber = sortedObjects_[axis].size() - leftNumber;
            auto boxPair = boundingBox_.split(
                    axis,
                    sortedObjects_[axis][leftNumber]->getMinimumAlongAxis(axis) - Geometry::EPS);
            Geometry::Float leftFunc = leftNumber * boxPair.first.getSurfaceArea();
            Geometry::Float rightFunc = rightNumber * boxPair.second.getSurfaceArea();
            if (minFunc < 0 || leftFunc + rightFunc < minFunc) {
                minFunc = leftFunc + rightFunc;
                bestAxis = axis;
                leftBox = boxPair.first;
                rightBox = boxPair.second;
            }
        }
    }
    axis_ = bestAxis;
    return std::pair<Geometry::BoundingBox, Geometry::BoundingBox>(leftBox, rightBox);
}

void KDNode::doSortObjects_()
{
    for (int axis = 0; axis < 3; ++axis) {
        sortedObjects_[axis] = objects_;
        std::sort(sortedObjects_[axis].begin(),
                  sortedObjects_[axis].end(),
                  [axis](IGraphObject *A, IGraphObject *B) -> bool {
                      return A->getMinimumAlongAxis(axis) <
                             B->getMinimumAlongAxis(axis);
                  }
        );
    }

}

bool KDNode::traceRay(const Geometry::Ray &ray, Geometry::Ray &normal)
{
    if (!boundingBox_.intersection(ray, normal)) {
        return false;
    }
    if (isLeaf()) {
        for (IGraphObject * objectPtr : objects_) {
            if (objectPtr->intersection(ray, normal))
                return true;
        }
        return false;
    }
    if (ray.getDirect().getAxisCoordinate(axis_) > 0) {
        // ray : -- >
        return left_->traceRay(ray, normal) || right_->traceRay(ray, normal);
    }
    // ray : < --
    return right_->traceRay(ray, normal) || left_->traceRay(ray, normal);
}

bool KDNode::isLeaf() const
{
    return left_ == nullptr || right_ == nullptr;
}

KDNode::~KDNode()
{
//    delete left_;
//    delete right_;
}
