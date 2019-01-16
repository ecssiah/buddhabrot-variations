#ifndef FRACTAL_IMAGE_H
#define FRACTAL_IMAGE_H

#include <array>
#include <vector>
#include <complex>
#include <random>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <ctime>

#include <Eigen/Geometry>
#include <Magick++.h>

#include "Constants.hpp"

using namespace std;
using namespace Eigen;
using namespace Magick;

struct ViewBox
{
  ViewBox(double x_, double y_, double w_, double h_)
    : x(x_), y(y_), w(w_), h(h_)
  {}

  double x;
  double y;
  double w;
  double h;
};


class FractalInstance
{  
  void build();

  Vector2d to_screen_coords(complex<double> c);

  default_random_engine generator;

  unsigned iterations;
  double escape_radius;

  ViewBox viewbox;

  vector<double> coefficients;
  vector<double> exponents; 

  vector<double> hue;

public:
  FractalInstance(
    vector<double> coefficients = {1, 1, 1}, 
    vector<double> exponents = {3, 2, 1},
    ViewBox viewbox = {0, 0, complex_range, complex_range},
    unsigned iterations = default_iterations, 
    double escape_radius = default_radius
  );

  vector< vector<unsigned> > counters;

  const double get_max_count();
  const vector<double> get_hue();

  void set_coefficients(vector<double> coefficients);
  void set_exponents(vector<double> exponents);
  void set_view(double x, double y, double w, double h);
  void set_hue(double r, double g, double b);

  static double default_radius;
  static double complex_range;

  static unsigned long long num_points;
  static unsigned default_iterations;
};

#endif // FRACTAL_IMAGE_H
