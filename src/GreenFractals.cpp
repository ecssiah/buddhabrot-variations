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

// user literal for millions (i.e. 1_m = 10000000)
constexpr unsigned long long operator "" _m(unsigned long long l) {
  return l * 1000 * 1000;
}

int main(int argc, char** argv)
{
  InitializeMagick(*argv);
  
  auto theta(0.0);
  auto delta(2 * M_PI / 100);
  
  Vector3f axis1(1, 1, 0);
  axis1.normalize();

  Vector3f vec(-1/720.0, -1/24.0, -1/2.0);
  auto vec1(vec);

  FractalInstance::num_points = 20000_m;
  FractalInstance::complex_range = 6.0;
  FractalInstance::default_radius = 2e0;
  FractalInstance::default_iterations = 1e2;

  FractalInstance fi(
    {1, 1/2.0, 1/6.0, 1/24.0, 1/120.0, 1/720.0, 1/5040.0, 1/40320.0},
    {1, 2, 3, 4, 5, 6, 7, 8},
    {0, 0, .56, .56}
  );

  ImageGenerator::generate(fi);

  /* for (auto frame(1); frame <= NUM_FRAMES; ++frame) */
  /* { */
  /*   FractalInstance fi( */
  /*     {vec1.x(), vec1.y(), vec1.z(), -1}, */
  /*     {6, 4, 2, 1} */
  /*   ); */

  /*   ImageGenerator::generate(fi, frame); */

  /*   theta += delta; */
  /*   auto t1(AngleAxis<float>(theta, axis1)); */
  /*   vec1 = t1 * vec; */
  /* } */
  
  return 0;
}
