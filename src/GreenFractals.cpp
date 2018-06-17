#include <cmath>
#include <vector>
#include <iostream>

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
  Vector3f vec(1, 1, 1);
  auto vec1(vec);
  
  axis1.normalize();

  FractalInstance::num_points = 4e6;
  FractalInstance::complex_range = 3.8;
  FractalInstance::default_radius = 2e0;
  FractalInstance::default_iterations = 2e2;

  FractalInstance fi1(
    {1, 1/2.0, 1/6.0, 1/24.0, 1/120.0, 1/720.0, 1/5040.0, 1/40320.0}, 
    {1, 2, 3, 4, 5, 6, 7, 8}
  );

  ImageGenerator::generate(fi1);

  FractalInstance fi2(
    {1, -1/2.0, 1/6.0, -1/24.0, 1/120.0, -1/720.0, 1/5040.0, -1/40320.0}, 
    {1, 2, 3, 4, 5, 6, 7, 8}
  );

  ImageGenerator::generate(fi2);

  for (auto frame(1); frame <= NUM_FRAMES; ++frame)
  {
    theta += delta;
    auto t1(AngleAxis<float>(theta, axis1));
    vec1 = t1 * vec;
  }
  
  return 0;
}
