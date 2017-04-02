cmake_minimum_required(VERSION 3.6)
project(mipt-algo2017-ray-tracing)

set(CMAKE_CXX_STANDARD 14)
find_package(Qt5Widgets REQUIRED)

set(SOURCE_FILES source/main.cpp source/main.cpp
        source/geometry/Vector.cpp source/geometry/Vector.h
        source/geometry/Point.cpp source/geometry/Point.h source/geometry/Sphere.cpp source/geometry/Sphere.h source/geometry/Triangle.cpp source/geometry/Triangle.h source/geometry/Ray.cpp source/geometry/Ray.h source/graphics/IGraphObject.h source/graphics/GraphSphere.cpp source/graphics/GraphSphere.h source/graphics/GraphScene.cpp source/graphics/GraphScene.h source/graphics/Illuminant.cpp source/graphics/Illuminant.h source/geometry/Surface.cpp source/geometry/Surface.cpp source/geometry/Surface.h source/graphics/GraphTriangle.cpp source/graphics/GraphTriangle.h source/parsers/parserObj.cpp source/parsers/parserObj.h source/geometry/Quadrangle.cpp source/geometry/Quadrangle.h)
add_executable(mipt-algo2017-ray-tracing ${SOURCE_FILES})
target_link_libraries(mipt-algo2017-ray-tracing Qt5::Widgets)