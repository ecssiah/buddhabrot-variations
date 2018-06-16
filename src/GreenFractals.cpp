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
#include "FractalInstance.hpp"

using namespace std;
using namespace Eigen;
using namespace Magick;

vector<FractalInstance> fractals;
array<double, 3 * SCREEN_SIZE * SCREEN_SIZE> pixels;


int main(int argc, char** argv)
{
  InitializeMagick(*argv);
  
  auto theta(0.0);
  auto delta(2 * M_PI / 100);
  
  Vector3f axis1(0, 1, 0);
  
  Vector3f vec(-.1, 1, -1);
  auto vec1(vec), vec2(vec), vec3(vec);
  Vector3f hue(1.00, 1.00, 1.00);
  
  axis1.normalize();

  FractalInstance::default_iterations = 1e2;
  FractalInstance::default_radius = 1.6;

  for (auto frame(0); frame < NUM_FRAMES; ++frame)
  {
    FractalInstance fi({vec1.x(), vec1.y(), vec1.z()}, {4, 2, 1});
    
    auto max(fi.get_max_count());
    
    for (auto x(0); x < SCREEN_SIZE; ++x)
    {
      for (auto y(0); y < SCREEN_SIZE; ++y)
      {
        auto value((double)fi.counters[x][y] / max);
        
        pixels[3 * (x + y * SCREEN_SIZE) + 0] = hue[0] * value;
        pixels[3 * (x + y * SCREEN_SIZE) + 1] = hue[1] * value;
        pixels[3 * (x + y * SCREEN_SIZE) + 2] = hue[2] * value;
      }
    }
    
    theta += delta;
    
    auto t1(AngleAxis<float>(theta, axis1));
    
    vec1 = t1 * vec;
    
    ostringstream pathstream;
    pathstream << "frames/frame" << std::setfill('0') << std::setw(4) << frame << ".jpg";
    
    Image image(SCREEN_SIZE, SCREEN_SIZE, "RGB", DoublePixel, &pixels);
    image.write(pathstream.str());
  }
  
  return 0;
}
