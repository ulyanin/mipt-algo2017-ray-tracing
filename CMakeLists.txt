cmake_minimum_required(VERSION 3.6)
project(mipt-algo2017-ray-tracing)

set(CMAKE_CXX_STANDARD 14)
find_package(Qt5Widgets REQUIRED)

set(SOURCE_FILES source/main.cpp source/main.cpp source/geometry/Vector.cpp source/geometry/Vector.h)
add_executable(mipt-algo2017-ray-tracing ${SOURCE_FILES})
target_link_libraries(mipt-algo2017-ray-tracing Qt5::Widgets)