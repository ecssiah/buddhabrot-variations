cmake_minimum_required (VERSION 3.0)
project (GreenFractals)

set(
  HEADERS
  ./src/Constants.hpp
  ./src/FractalInstance.hpp
)

set(
  SOURCES
  ./src/FractalInstance.cpp
  ./src/GreenFractals.cpp
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

target_compile_options(
  GreenFractals PRIVATE
  "-DMAGICKCORE_QUANTUM_DEPTH=16"
  "-DMAGICKCORE_HDRI_ENABLE=0"
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/frames)
