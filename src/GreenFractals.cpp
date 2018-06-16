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

double fact(double n)
{
  return (n == 1 || n == 0) ? 1 : fact(n - 1) * n;
}

int main(int argc, char** argv)
{
  InitializeMagick(*argv);
  
  auto theta(0.0);
  auto delta(2 * M_PI / 100);
  
  Vector3f axis1(1, 1, 0);
  Vector3f vec(1, 1 / fact(2), 1 / fact(3));
  auto vec1(vec);
  
  axis1.normalize();

  FractalInstance::default_radius = 3;
  FractalInstance::default_iterations = 4e3;

  for (auto frame(0); frame < NUM_FRAMES; ++frame)
  {
    FractalInstance fi(
      {1, 1, 1/fact(2), 1/fact(3), 1/fact(4), 1/fact(5), 1/fact(6)}, 
      {0, 1, 2,         3,         4,         5,         6}
    );

    ImageGenerator::generate(fi, frame);

    theta += delta;
    auto t1(AngleAxis<float>(theta, axis1));
    
    vec1 = t1 * vec;
  }
  
  return 0;
}
