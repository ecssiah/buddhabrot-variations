#include <array>
#include <chrono>
#include <complex>
#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>

#include <Eigen/Geometry>
#include <Magick++.h>

#include "Constants.hpp"
#include "ImageGenerator.hpp"
#include "FractalInstance.hpp"

using namespace std;
using namespace Eigen;
using namespace Magick;

vector<FractalInstance> fractals;

int main(int argc, char** argv)
{
  InitializeMagick(*argv);
  
  auto theta(0.0);
  auto delta(2 * M_PI / 100);
  
  Vector3f axis1(1, 1, 0);
  Vector3f vec(.8, -.5, -1);
  auto vec1(vec), vec2(vec), vec3(vec);
  
  axis1.normalize();

  FractalInstance::default_radius = 1.6;
  FractalInstance::default_iterations = 1e3;

  for (auto frame(0); frame < NUM_FRAMES; ++frame)
  {
    FractalInstance fi({vec1.x(), vec1.y(), vec1.z()}, {4, 2, 1});

    ImageGenerator::generate(fi, frame);

    theta += delta;
    auto t1(AngleAxis<float>(theta, axis1));
    
    vec1 = t1 * vec;
  }
  
  return 0;
}
