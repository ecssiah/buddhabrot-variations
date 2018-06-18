#include <cmath>
#include <complex>
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
  axis1.normalize();

  Vector3f vec(-1/720.0, -1/24.0, -1/2.0);
  auto vec1(vec);

  FractalInstance::num_points = 4e6;
  FractalInstance::complex_range = 4.0;
  FractalInstance::default_radius = 2e0;
  FractalInstance::default_iterations = 1e2;

  for (auto frame(1); frame <= NUM_FRAMES; ++frame)
  {
    FractalInstance fi(
      {vec1.x(), vec1.y(), vec1.z(), -1},
      {6, 4, 2, 1}
    );

    ImageGenerator::generate(fi, frame);

    theta += delta;
    auto t1(AngleAxis<float>(theta, axis1));
    vec1 = t1 * vec;
  }
  
  return 0;
}
