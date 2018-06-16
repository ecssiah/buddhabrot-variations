#ifndef FRACTAL_IMAGE_H
#define FRACTAL_IMAGE_H

#include <array>

#include "Constants.hpp"

class FractalInstance
{  
  unsigned iterations;
  double escape_radius;

  vector<double> coefficients;
  vector<double> exponents; 

  CounterArray counters;

  void build();

  double get_max_count();
  Vector2d to_screen_coords(complex<double> c);

public:
  FractalInstance(
    vector<double> coefficients = {1, 1, 1}, 
    vector<double> exponents = {3, 2, 1},
    unsigned iterations = 100, double escape_radius = 1.0
  );

  void setCoefficients(vector<double> coefficients);
  void setExponents(vector<double> exponents);
};

#endif // FRACTAL_IMAGE_H
