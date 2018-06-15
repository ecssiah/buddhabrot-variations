#ifndef GREENFRACTALS_H
#define GREENFRACTALS_H

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

constexpr auto COMPLEX_RANGE(3.0);
constexpr auto NUM_POINTS(4.6e6);

constexpr auto NUM_FRAMES(100);
constexpr auto SCREEN_SIZE(1024);
constexpr auto CONVERSION_FACTOR(SCREEN_SIZE / COMPLEX_RANGE);

using namespace std;
using namespace Eigen;
using namespace Magick;

using CounterArray = array<array<int, SCREEN_SIZE>, SCREEN_SIZE>;

class GreenFractals 
{
  CounterArray ch1_counters;
  CounterArray ch2_counters;
  CounterArray ch3_counters;

  array<double, 3 * SCREEN_SIZE * SCREEN_SIZE> pixels;

  default_random_engine RNG;

public:
  GreenFractals();

private:
  Vector2d to_screen_coords(complex<double> c);

  double get_max_count(CounterArray& counters);

  void fill_counters(
    CounterArray& counters, 
    unsigned int iterations, double escape_radius, 
    double p, double q, double r
  );
};

#endif /* GREENFRACTALS_H */
