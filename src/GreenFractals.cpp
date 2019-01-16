#include <cmath>
#include <complex>
#include <vector>
#include <iostream>

#include <Eigen/Geometry>
#include <Magick++.h>

#include "Constants.h"
#include "ImageGenerator.h"
#include "FractalInstance.h"

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
  auto delta(2 * M_PI / NUM_FRAMES);

  auto offset1(0.0);
  auto offset2(0.0);
  auto offset3(0.0);
  
  Vector3f axis1(1, 0, 0);
  Vector3f axis2(0, 1, 0);
  Vector3f axis3(0, 0, 1);

  axis1.normalize();
  axis2.normalize();
  axis3.normalize();

  Vector3f vec(-1/6.0, 1/120.0, -1/5040.0);
  auto vec1(vec);
  auto vec2(vec);
  auto vec3(vec);

  FractalInstance::num_points = 10_m;
  FractalInstance::complex_range = 6.0;
  FractalInstance::default_iterations = 1e2;

  /* FractalInstance fi( */
  /*   {1, vec1.x(), vec1.y(), vec1.z()}, */
  /*   {1, 2, 4, 6}, */
  /*   {0, 0, 3.0, 3.0} */
  /* ); */

  /* ImageGenerator::generate(fi); */

  for (auto frame(1); frame <= NUM_FRAMES; ++frame)
  {
    FractalInstance rfi(
      {1, vec1.x(), vec1.y(), vec1.z()},
      {1, 2, 4, 6},
      {0, 0, 4.0, 4.0}
    );

    FractalInstance gfi(
      {1, vec2.x(), vec2.y(), vec2.z()},
      {1, 2, 4, 6},
      {0, 0, 4.0, 4.0}
    );

    FractalInstance bfi(
      {1, vec3.x(), vec3.y(), vec3.z()},
      {1, 2, 4, 6},
      {0, 0, 4.0, 4.0}
    );

    ImageGenerator::generate({rfi, gfi, bfi}, frame);

    theta += delta;
    auto t1(AngleAxis<float>(theta + offset1, axis1));
    vec1 = t1 * vec;
    auto t2(AngleAxis<float>(theta + offset2, axis2));
    vec2 = t2 * vec;
    auto t3(AngleAxis<float>(theta + offset3, axis3));
    vec3 = t3 * vec;
  }
  
  return 0;
}
