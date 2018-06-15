#include <Eigen/Geometry>
#include <Magick++.h>

#include <array>
#include <chrono>
#include <complex>
#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "Constants.hpp"

using namespace Eigen;
using namespace Magick;
using namespace std;

static mt19937 RNG;

using CounterArray = array<array<int, SCREEN_SIZE>, SCREEN_SIZE>;

CounterArray ch1_counters;

array<double, 3 * SCREEN_SIZE * SCREEN_SIZE> pixels;


Vector2d to_screen_coords(complex<double> c)
{
  return {
    CONVERSION_FACTOR * c.real() + SCREEN_SIZE / 2,
    CONVERSION_FACTOR * c.imag() + SCREEN_SIZE / 2
  };
}


double get_max_count(CounterArray& counters)
{
  auto max_count(0);
  
  for (const auto& row : counters)
    for (const auto& count : row)
      if (count > max_count) max_count = count;
  
  return max_count;
}


void fill_counters(
  CounterArray& counters, unsigned int iterations, double escape_radius, double p, double q, double r)
{
  for (auto& row : counters) row.fill(0);
  
  for (auto i(0); i < NUM_POINTS; ++i)
  {
    uniform_real_distribution<> dist(-COMPLEX_RANGE/2, COMPLEX_RANGE/2);
    
    complex<double> z;
    complex<double> C(dist(RNG), dist(RNG));
    
    vector<complex<double>> path;
    
    for (auto j(0); j < iterations; ++j)
    {
      auto w(conj(z));
      
      z = p * pow(w, 3) + q * pow(w, 2) + r * pow(w, 1) + C;
      
      path.push_back(z);
      
      if (abs(z) > escape_radius)
      {
        for (auto c : path)
        {
          auto pos1(to_screen_coords(c));
          
          if (pos1.x() > 0 && pos1.x() < SCREEN_SIZE && pos1.y() > 0 && pos1.y() < SCREEN_SIZE)
          {
            auto pos2(to_screen_coords({ c.real(),-c.imag()}));

            counters[pos1.y()][pos1.x()] += 1;
            counters[pos2.y()][pos2.x()] += 1;
          }
        }
        break;
      }
    }
  }
}


int main(int argc, char** argv)
{
  InitializeMagick(*argv);
  
  RNG.seed(static_cast<unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
  
  auto theta(0.0);
  auto delta(1e-1);
  
  Vector3f axis1(0, 1, 0);
  
  Vector3f vec(.3, .4, 1);
  auto vec1(vec), vec2(vec), vec3(vec);
  Vector3f hue(1.00, 1.00, 1.00);
  
  axis1.normalize();

  for (auto frame(0); frame < NUM_FRAMES; ++frame)
  {
    fill_counters(ch1_counters, 100, 1.0, vec1.x(), vec1.y(), vec1.z());
    
    auto ch1_max(get_max_count(ch1_counters));
    
    for (auto x(0); x < SCREEN_SIZE; ++x)
    {
      for (auto y(0); y < SCREEN_SIZE; ++y)
      {
        auto ch1_value((double)ch1_counters[x][y] / ch1_max);
        
        pixels[3 * (x + y * SCREEN_SIZE) + 0] = hue[0] * ch1_value;
        pixels[3 * (x + y * SCREEN_SIZE) + 1] = hue[1] * ch1_value;
        pixels[3 * (x + y * SCREEN_SIZE) + 2] = hue[2] * ch1_value;
      }
    }
    
    theta += delta;
    
    auto t1(AngleAxis<float>(theta, axis1));
    
    vec1 = t1 * vec;
    
    ostringstream pathstream;
    pathstream << "build/frame" << std::setfill('0') << std::setw(4) << frame << ".jpg";
    
    Image image(SCREEN_SIZE, SCREEN_SIZE, "RGB", DoublePixel, &pixels);
    image.write(pathstream.str());
  }
  
  return 0;
}
