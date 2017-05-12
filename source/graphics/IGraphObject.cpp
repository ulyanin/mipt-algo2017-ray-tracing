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

IGraphObject::IGraphObject() :
        boundingBox_(Geometry::BoundingBox()),
        material_(GraphMaterial())
{ }

IGraphObject::IGraphObject(const Geometry::BoundingBox &boundingBox,
                           const GraphMaterial &material) :
        boundingBox_(boundingBox),
        material_(material)
{

}

GraphMaterial IGraphObject::getMaterial() const
{
    return material_;
}
