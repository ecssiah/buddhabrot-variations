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

add_executable(GreenFractals ${HEADERS} ${SOURCES})

target_compile_features(GreenFractals PRIVATE cxx_range_for)

find_package(Eigen3 REQUIRED)
find_package(ImageMagick REQUIRED)

include_directories(
  ${EIGEN3_INCLUDE_DIR}
  ${ImageMagick_INCLUDE_DIRS}
)

target_link_libraries(
  GreenFractals
  ${ImageMagick_LIBRARIES}
)

