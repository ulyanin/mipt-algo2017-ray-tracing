//
// Created by ulyanin on 06.04.17.
//

#include "BoundingBox.h"
#include "Quadrangle.h"

namespace Geometry
{
    std::array<Geometry::Vector, 3> BoundingBox::AXISES = {
            Geometry::Vector(1, 0, 0),
            Geometry::Vector(0, 1, 0),
            Geometry::Vector(0, 0, 1)
    };

    BoundingBox::BoundingBox(const Point &pointMin, const Point &pointMax) :
            pMin_(pointMin),
            pMax_(pointMax)
    {

    }

    const Point &BoundingBox::getPMin() const
    {
        return pMin_;
    }

    const Point &BoundingBox::getPMax() const
    {
        return pMax_;
    }

    BoundingBox::BoundingBox(std::initializer_list<Point> initializerList)
    {
        Float minA[3];
        Float maxA[3];
        for (int i = 0; i < 3; ++i) {
            minA[i] = std::min_element(
                    initializerList.begin(), initializerList.end(),
                    [i] (const Point &A, const Point &B) -> bool {
                        return A.getAxisCoordinate(i) < B.getAxisCoordinate(i);
                    }
            )->getAxisCoordinate(i);
            maxA[i] = std::max_element(
                    initializerList.begin(),
                    initializerList.end(),
                    [i] (const Point &A, const Point &B) -> bool {
                        return A.getAxisCoordinate(i) < B.getAxisCoordinate(i);
                    }
            )->getAxisCoordinate(i);
        }
        pMin_ = Point(minA[0], minA[1], minA[2]);
        pMax_ = Point(maxA[0], maxA[1], maxA[2]);
    }

    Float BoundingBox::getLengthAlongAxis(int axisNumber) const
    {
        return Vector(pMin_, pMax_).getAxisCoordinate(axisNumber);
    }

    std::pair<BoundingBox, BoundingBox> BoundingBox::split(int axis, Float coordinate) const
    {
        Point midLeft, midRight;
        if (axis == 0) {
            midLeft = Point(coordinate, pMax_.getY(), pMax_.getZ());
            midRight = Point(coordinate, pMin_.getY(), pMin_.getZ());
        } else if (axis == 1) {
            midLeft = Point(pMax_.getX(), coordinate, pMax_.getZ());
            midRight = Point(pMin_.getX(), coordinate, pMin_.getZ());
        } else {
            midLeft = Point(pMax_.getX(), pMax_.getY(), coordinate);
            midRight = Point(pMin_.getX(), pMin_.getZ(), coordinate);
        }
//        std::cerr << "____" << std::endl;
//        std::cerr << pMin_ << "; " << pMax_ << std::endl;
//        std::cerr << midLeft << "; " << midRight << std::endl;
//        std::cerr << axis << " " << coordinate << std::endl;
//        std::cerr << Vector(pMin_, midLeft) << std::endl;
//        std::cerr << Vector(midRight, pMax_) << std::endl;
        if (Vector(pMin_, midLeft).getX() < -1e-4)
            throw std::invalid_argument("split negative x");
        if (Vector(pMin_, midLeft).getY() < -1e-4)
            throw std::invalid_argument("split negative y");
        if (Vector(pMin_, midLeft).getZ() < -1e-4)
            throw std::invalid_argument("split negative z");
        if (Vector(midRight, pMax_).getX() < -1e-4)
            throw std::invalid_argument("split negative x");
        if (Vector(midRight, pMax_).getY() < -1e-4)
            throw std::invalid_argument("split negative y");
        if (Vector(midRight, pMax_).getZ() < -1e-4)
            throw std::invalid_argument("split negative z");
//        std::cout << Vector(pMin_, midLeft) << std::endl;
//        std::cout << Vector(midRight, pMax_) << std::endl;
        return std::make_pair(BoundingBox(pMin_, midLeft),
                              BoundingBox(midRight, pMax_));
    }

    Float BoundingBox::getSurfaceArea() const
    {
        Float xLen = getLengthAlongAxis(0);
        Float yLen = getLengthAlongAxis(1);
        Float zLen = getLengthAlongAxis(2);
        return 2 * (xLen * yLen + xLen * zLen + yLen * zLen);
    }

    bool BoundingBox::isInside(const Point &p) const
    {
        return
                pMin_.getX() <= p.getX() && p.getX() <= pMax_.getX() &&
                pMin_.getY() <= p.getY() && p.getY() <= pMax_.getY() &&
                pMin_.getZ() <= p.getZ() && p.getZ() <= pMax_.getZ();
    }

    bool BoundingBox::intersection(const Ray &ray, Ray &normal) const
    {
        Point points[2] = {pMin_, pMax_};
        int projection[6][4][3] = {
                { {0, 0, 0}, {0, 0, 1}, {0, 1, 1}, {0, 1, 0} },
                { {0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 0, 1} },
                { {0, 0, 0}, {0, 1, 0}, {1, 1, 0}, {1, 0, 0} },

                { {1, 1, 1}, {0, 1, 1}, {0, 0, 1}, {1, 0, 1} },
                { {1, 1, 1}, {1, 1, 0}, {0, 1, 0}, {0, 1, 1} },
                { {1, 1, 1}, {1, 0, 1}, {1, 0, 0}, {1, 1, 0} }
        };
        for (int i = 0; i < 6; ++i) {
            Point pts[4];
            for (int j = 0; j < 4; ++j) {
                pts[j] = Point(
                        points[projection[i][j][0]].getX(),
                        points[projection[i][j][1]].getY(),
                        points[projection[i][j][2]].getZ()
                );
            }
            Quadrangle quadrangle(
                    pts[0],
                    pts[1],
                    pts[2],
                    pts[3]
            );
            if (quadrangle.intersection(ray, normal)) {
                return true;
            }
        }
        return false;
    };

}