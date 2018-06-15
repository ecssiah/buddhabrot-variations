cmake_minimum_required (VERSION 3.0)
project (GreenFractals)

set(
  HEADERS
  ./GreenFractals.h
)

set(
  SOURCES
  ./GreenFractals.cxx
)

set(CMAKE_CXX_STANDARD 11)

add_executable(GreenFractals ${HEADERS} ${SOURCES})

find_package(Eigen3 REQUIRED)
find_package(ImageMagick COMPONENTS Magick++ REQUIRED)

include_directories(
  ${EIGEN3_INCLUDE_DIR}
  ${ImageMagick_INCLUDE_DIRS}
)

target_link_libraries(
  GreenFractals
  ${ImageMagick_LIBRARIES}
)

