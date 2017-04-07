#include "IGraphObject.h"

Geometry::Float IGraphObject::getMinimumAlongAxis(int axisNumber) const
{
    return Geometry::Vector(boundingBox_.getPMin()).dotProduct(
            Geometry::BoundingBox::AXISES[axisNumber]
    );
}

Geometry::Float IGraphObject::getMaximumAlongAxis(int axisNumber) const
{
    return Geometry::Vector(boundingBox_.getPMax()).dotProduct(
            Geometry::BoundingBox::AXISES[axisNumber]
    );
}

Geometry::BoundingBox IGraphObject::getBoundingBox() const
{
    return boundingBox_;
}
