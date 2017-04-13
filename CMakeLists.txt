cmake_minimum_required(VERSION 3.6)
project(mipt-algo2017-ray-tracing)

set(CMAKE_CXX_STANDARD 14)
find_package(Qt5Widgets REQUIRED)

#IF(CMAKE_COMPILER_IS_GNUCC)
#    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
#    set(CMAKE_EXE_LINKER_FLAGS "-s")
#ENDIF(CMAKE_COMPILER_IS_GNUCC)

set(SOURCE_FILES source/main.cpp source/main.cpp
        source/geometry/Vector.cpp source/geometry/Vector.h
        source/geometry/Point.cpp source/geometry/Point.h
        source/geometry/Sphere.cpp source/geometry/Sphere.h
        source/geometry/Triangle.cpp source/geometry/Triangle.h
        source/geometry/Ray.cpp source/geometry/Ray.h
        source/graphics/IGraphObject.h source/graphics/GraphSphere.cpp
        source/graphics/GraphSphere.h source/graphics/GraphScene.cpp
        source/graphics/GraphScene.h source/graphics/Illuminant.cpp
        source/graphics/Illuminant.h source/geometry/Surface.cpp
        source/geometry/Surface.cpp source/geometry/Surface.h
        source/graphics/GraphTriangle.cpp source/graphics/GraphTriangle.h
        source/parsers/ParserObj.cpp source/parsers/ParserObj.h
        source/geometry/Quadrangle.cpp source/geometry/Quadrangle.h
        source/graphics/GraphQuadrangle.cpp source/graphics/GraphQuadrangle.h
        source/graphics/GraphScreen.cpp source/graphics/GraphScreen.h
        source/graphics/KDTree.h source/graphics/KDTree.cpp
        source/graphics/KDNode.cpp source/graphics/KDNode.h
        source/geometry/BoundingBox.cpp source/geometry/BoundingBox.h
        source/graphics/IGraphObject.cpp source/graphics/GraphMaterial.cpp source/graphics/GraphMaterial.h source/graphics/GraphColor.cpp source/graphics/GraphColor.h)
add_executable(mipt-algo2017-ray-tracing ${SOURCE_FILES})
target_link_libraries(mipt-algo2017-ray-tracing Qt5::Widgets)