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

  FractalInstance::num_points = 1e7;
  FractalInstance::complex_range = 4.0;
  FractalInstance::default_radius = 2e0;
  FractalInstance::default_iterations = 1e2;

  FractalInstance fi(
    {-1/36.0, -1/16.0, -1/4.0, -1},
    {7, 5, 3, 1},
    {1.6, 0, .40, .40}
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
