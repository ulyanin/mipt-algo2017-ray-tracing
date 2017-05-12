//
// Created by ulyanin on 06.04.17.
//

#include <set>
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
//    std::cerr << boundingBox.getPMin() << " " << boundingBox.getPMax() << std::endl;
//    std::cerr << boundingBox.getVolume() << std::endl;
    doSortObjects_();

    if (objects_.size() <= MIN_OBJECT_NUMBER || depth >= MAX_DEPTH) {
//        std::cout << depth << std::endl;
        return;
    }

    auto pairBox = chooseSplit();
    if (pairBox.first.getVolume() < Geometry::EPS || pairBox.second.getVolume() < Geometry::EPS) {
        std::cout << "break" << std::endl;
//        std::cerr << objects_.size() << std::endl;
//        std::cerr << depth << std::endl;
//        std::cerr << boundingBox.getPMin() << " "<< boundingBox.getPMax() << std::endl;
//        std::cerr << pairBox.first.getPMin() << " "<< pairBox.first.getPMax() << std::endl;
//        std::cerr << pairBox.second.getPMin() <<" "<< pairBox.second.getPMax() << std::endl;
//        std::cerr << pairBox.first.getVolume() << " " << pairBox.second.getVolume() << std::endl;
//        throw ;
        return;
    }
    std::cout << depth << std::endl;
    std::cout << pairBox.first.getPMax() - pairBox.first.getPMin() << std::endl;
    std::cout << pairBox.second.getPMax() - pairBox.second.getPMin() << std::endl;
    std::vector<IGraphObject *> leftList;
    std::vector<IGraphObject *> rightList;
    for (IGraphObject * objectPtr : objects_) {
//        if (objectPtr->insideABox(pairBox.first)) {
//            leftList.push_back(objectPtr);
//        }
//        if (objectPtr->insideABox(pairBox.second)) {
//            rightList.push_back(objectPtr);
//        }
        bool f = 0;
        if (Geometry::lessOrEqual(objectPtr->getBoundingBox().getPMin().getAxisCoordinate(axis_),
                                  splitedCoordinate)) {
            leftList.push_back(objectPtr);
            f = 1;
        }
        if (Geometry::greaterOrEqual(objectPtr->getBoundingBox().getPMax().getAxisCoordinate(axis_),
                                     splitedCoordinate)) {
            rightList.push_back(objectPtr);
            f = 1;
        }

//        if (item->minPos(bestAxis) < bestPos)
//            left.push_back(item);
//        if (item->maxPos(bestAxis) > bestPos)
//            right.push_back(item);
        if (f == 0) {
            std::cout << depth << std::endl;
            std::cout << (std::find(objects_.begin(), objects_.end(), objectPtr) - objects_.begin()) << std::endl;
            std::cout << boundingBox.getPMin() << " "<< boundingBox.getPMax() << std::endl;
            std::cout << pairBox.first.getPMin() << " "<< pairBox.first.getPMax() << std::endl;
            std::cout << pairBox.second.getPMin() <<" "<< pairBox.second.getPMax() << std::endl;
            std::cout << objectPtr->getBoundingBox().getPMin() << " "
                      << objectPtr->getBoundingBox().getPMax() << std::endl;

            throw std::runtime_error("object does not have someplace");
        }
    }
    left_ = new KDNode(leftList);
    right_ = new KDNode(rightList);
    left_->buildTree(pairBox.first, depth + 1);
    right_->buildTree(pairBox.second, depth + 1);


//    std::set<IGraphObject *> all(objects_.begin(), objects_.end());
//    std::set<IGraphObject *> child;
//    for (auto obj : left_->objects_) {
//        child.insert(obj);
//        if (all.count(obj) == 0) {
//            throw std::runtime_error("left child does not exit in all");
//        }
//    }
//    for (auto obj : right_->objects_) {
//        child.insert(obj);
//        if (all.count(obj) == 0) {
//            throw std::runtime_error("right child does not exit in all");
//        }
//    }
//    for (auto  obj : all) {
//        if (child.count(obj) == 0) {
//            throw std::runtime_error("all >= child");
//        }
//    }

}


std::pair<Geometry::BoundingBox, Geometry::BoundingBox> KDNode::chooseSplit()
{
    int bestAxis = 0;
    Geometry::BoundingBox leftBox, rightBox;
    Geometry::Float minFunc = -1;

//    axis_ = rand() % 3;
//    splitedCoordinate = (boundingBox_.getPMin() + boundingBox_.getPMax()).getAxisCoordinate(axis_) / 2;
//    return boundingBox_.split(axis_, splitedCoordinate);


    for (int axis = 0; axis < 3; ++axis) {

        for (size_t leftNumber = 0; leftNumber < sortedObjectsMin_[axis].size(); ++leftNumber) {
            size_t rightNumber = sortedObjectsMin_[axis].size() - leftNumber;
            /*
             * means that this object intersect neighbour
             * bounding box, so, his leftest border is lefter
             * then our left bounding box border
             */
            if (boundingBox_.isInside(
                    sortedObjectsMin_[axis][leftNumber]->getBoundingBox().getPMin())) {
                auto boxPair = boundingBox_.split(
                        axis,
                        sortedObjectsMin_[axis][leftNumber]->getMinimumAlongAxis(axis) - Geometry::EPS);

                Geometry::Float leftFunc = leftNumber * boxPair.first.getSurfaceArea();
                Geometry::Float rightFunc = rightNumber * boxPair.second.getSurfaceArea();
                //            std::cerr << axis << " " << leftFunc << " " << rightFunc << " " << leftFunc + rightFunc << " " << minFunc << std::endl;
                if (minFunc < 0 || leftFunc + rightFunc < minFunc) {
                    minFunc = leftFunc + rightFunc;
                    axis_ = bestAxis = axis;
                    splitedCoordinate = sortedObjectsMin_[axis][leftNumber]->getMinimumAlongAxis(axis) - Geometry::EPS;
                    leftBox = boxPair.first;
                    rightBox = boxPair.second;
                }
            }
            if (boundingBox_.isInside(
                    sortedObjectsMax_[axis][leftNumber]->getBoundingBox().getPMax())) {
                auto boxPair = boundingBox_.split(
                        axis,
                        sortedObjectsMax_[axis][leftNumber]->getMaximumAlongAxis(axis) + Geometry::EPS);

                Geometry::Float leftFunc = leftNumber * boxPair.first.getSurfaceArea();
                Geometry::Float rightFunc = rightNumber * boxPair.second.getSurfaceArea();
                //            std::cerr << axis << " " << leftFunc << " " << rightFunc << " " << leftFunc + rightFunc << " " << minFunc << std::endl;
                if (minFunc < 0 || leftFunc + rightFunc < minFunc) {
                    minFunc = leftFunc + rightFunc;
                    axis_ = bestAxis = axis;
                    splitedCoordinate = sortedObjectsMax_[axis][leftNumber]->getMaximumAlongAxis(axis) + Geometry::EPS;
                    leftBox = boxPair.first;
                    rightBox = boxPair.second;
                }
            }


        }
    }
    axis_ = bestAxis;
    return std::pair<Geometry::BoundingBox, Geometry::BoundingBox>(leftBox, rightBox);
}

void KDNode::doSortObjects_()
{
    for (int axis = 0; axis < 3; ++axis) {
        sortedObjectsMin_[axis] = objects_;
        std::sort(sortedObjectsMin_[axis].begin(),
                  sortedObjectsMin_[axis].end(),
                  [axis](IGraphObject *A, IGraphObject *B) -> bool {
                      return A->getMinimumAlongAxis(axis) <
                             B->getMinimumAlongAxis(axis);
                  }
        );
        sortedObjectsMax_[axis] = objects_;
        std::sort(sortedObjectsMax_[axis].begin(),
                  sortedObjectsMax_[axis].end(),
                  [axis](IGraphObject *A, IGraphObject *B) -> bool {
                      return A->getMaximumAlongAxis(axis) <
                             B->getMaximumAlongAxis(axis);
                  }
        );
    }

}



bool KDNode::stupidIntersection(const Geometry::Ray &ray, Geometry::Ray &normal,
                                GraphMaterial & material) const
{
    Geometry::Ray normalNearest;
    bool wasIntersection = false;
    for (IGraphObject * obj : objects_) {
        if (obj->intersection(ray, normal) && boundingBox_.isInside(normal.getBegin())) {
            if (!wasIntersection || Geometry::Vector(normal.getBegin(), ray.getBegin()).length2() <
                                    Geometry::Vector(normalNearest.getBegin(), ray.getBegin()).length2()) {
                wasIntersection = true;
                normalNearest = normal;
                material = obj->getMaterial();
            }
        }
    }
    normal = normalNearest;
    return wasIntersection;
}

bool KDNode::traceRay(const Geometry::Ray &ray, Geometry::Ray &normal, GraphMaterial &material)
{
    if (!boundingBox_.intersection(ray, normal)) {
        return false;
    }
    if (isLeaf()) {
        return stupidIntersection(ray, normal, material);
    }
    if (ray.getDirect().getAxisCoordinate(axis_) > 0) {
        // ray : -- >
        return left_->traceRay(ray, normal, material) || right_->traceRay(ray, normal, material);
    }
    // ray : < --
    return right_->traceRay(ray, normal, material) || left_->traceRay(ray, normal, material);

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

const char *KDNode::whereIs(const Geometry::Point &P) const
{
    if (!boundingBox_.isInside(P)) {
        return "nowhere";
    }
    if (isLeaf()) {
        return "Leaf";
    }
    if (left_->boundingBox_.isInside(P)) {
        return "left";
    }
    if (right_->boundingBox_.isInside(P)) {
        return "right";
    }
    return "is not true";
}
