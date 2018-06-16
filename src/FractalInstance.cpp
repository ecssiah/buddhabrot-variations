#include "FractalInstance.hpp"

unsigned FractalInstance::default_iterations = 100;
double FractalInstance::default_radius = 1.0;

FractalInstance::FractalInstance(
  vector<double> coefficients_, vector<double> exponents_,
  unsigned iterations_, double escape_radius_ 
)
  : coefficients(coefficients_),
    exponents(exponents_),
    iterations(iterations_),
    escape_radius(escape_radius_),
    pixels(3 * SCREEN_SIZE * SCREEN_SIZE)
{
  
}


void FractalInstance::setCoefficients(vector<double> coefficients_)
{
  coefficients = coefficients_; 
}

void FractalInstance::setExponents(vector<double> exponents_)
{
  exponents = exponents_;
}

Vector2d FractalInstance::to_screen_coords(complex<double> c)
{
  return {
    CONVERSION_FACTOR * c.real() + SCREEN_SIZE / 2,
    CONVERSION_FACTOR * c.imag() + SCREEN_SIZE / 2
  };
}


double FractalInstance::get_max_count()
{
  auto max_count(0);
  
  for (const auto& row : counters)
    for (const auto& count : row)
      if (count > max_count) max_count = count;
  
  return max_count;
}


void FractalInstance::build()
{
  for (auto& row : counters) row.fill(0);
  
  for (auto i(0); i < NUM_POINTS; ++i)
  {
    uniform_real_distribution<> dist(-COMPLEX_RANGE/2, COMPLEX_RANGE/2);
    
    complex<double> z;
    complex<double> C(dist(generator), dist(generator));
    
    vector<complex<double>> path;
    
    for (auto j(0); j < iterations; ++j)
    {
      auto w(conj(z));
      
      z = C;

      for (int i = 0; i < coefficients.size(); ++i)
      {
        z += coefficients[i] * pow(w, exponents[i]);
      }
      
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

