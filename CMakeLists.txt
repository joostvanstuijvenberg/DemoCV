cmake_minimum_required(VERSION 3.12)
project(DemoCV)
find_package(OpenCV REQUIRED)
find_package(X11 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${X11_INCLUDE_DIRS})

set (CMAKE_CXX_STANDARD 14)
add_executable (DemoCV DemoCV.cpp BasicMorphologyDemo.cpp CircularWindowStrategy.cpp EdgeDetectionDemo.cpp
        ShiftedWindowStrategy.cpp ThresholdDemo.cpp BitPlaneSlicingDemo.cpp ColorDemo.cpp
        Demo.cpp SmoothingDemo.cpp BlobDetectionDemo.cpp Demo.cpp RegionOfInterestDemo.cpp
        StackedWindowStrategy.cpp)
target_link_libraries (DemoCV ${OpenCV_LIBS} ${X11_LIBRARIES})
