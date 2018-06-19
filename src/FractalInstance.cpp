#include "FractalInstance.hpp"

unsigned long long FractalInstance::num_points = 1e6;
unsigned FractalInstance::default_iterations = 100;

double FractalInstance::default_radius = 1.0;
double FractalInstance::complex_range = 3.6;

FractalInstance::FractalInstance(
  vector<double> coefficients_, vector<double> exponents_,
  ViewBox viewbox_,
  unsigned iterations_, double escape_radius_ 
)
  : coefficients(coefficients_),
    exponents(exponents_),
    iterations(iterations_),
    viewbox(viewbox_),
    escape_radius(escape_radius_),
    counters(SCREEN_SIZE, vector<unsigned>(SCREEN_SIZE))
{
  generator.seed(time(nullptr));

  build();  
}


void FractalInstance::setCoefficients(vector<double> coefficients_)
{
  coefficients = coefficients_; 
}

void FractalInstance::setExponents(vector<double> exponents_)
{
  exponents = exponents_;
}

void FractalInstance::setView(double x_, double y_, double w_, double h_) 
{
  viewbox.x = x_;
  viewbox.y = y_;
  viewbox.w = w_;
  viewbox.h = h_;
}

Vector2d FractalInstance::to_screen_coords(complex<double> c)
{
  auto width_conversion = SCREEN_SIZE / viewbox.w;
  auto height_conversion = SCREEN_SIZE / viewbox.h;

  return {
    width_conversion * (c.imag() - viewbox.x + viewbox.w / 2),
    height_conversion * (c.real() - viewbox.y + viewbox.h / 2)
  };
}


const double FractalInstance::get_max_count()
{
  auto max_count(0);
  
  for (const auto& row : counters)
    for (const auto& count : row)
      if (count > max_count) max_count = count;
  
  return max_count;
}


void FractalInstance::build()
{
  for (auto& row : counters) fill(row.begin(), row.end(), 0);
  
  for (auto i(0); i < num_points; ++i)
  {
    uniform_real_distribution<> dist(-complex_range / 2, complex_range / 2);
    
    complex<double> z;
    complex<double> C(dist(generator), dist(generator));
    
    vector<complex<double>> path;
    
    for (auto j(0); j < iterations; ++j)
    {
      auto w(conj(z));

      z = C;

      for (int i = 0; i < coefficients.size(); ++i)
        z += coefficients[i] * pow(w, exponents[i]);
      
      path.push_back(z);
      
      if (abs(z) > escape_radius)
      {
        for (auto c : path)
        {
          auto top(c.real() <= viewbox.y + viewbox.h / 2);
          auto bottom(c.real() >= viewbox.y - viewbox.h / 2);

          if (top && bottom)
          {
            auto left1(c.imag() >= viewbox.x - viewbox.w / 2); 
            auto right1(c.imag() <= viewbox.x + viewbox.w / 2);

            if (left1 && right1)
            {
              auto pos1(to_screen_coords(c));
              counters[pos1.x()][pos1.y()] += 1;
            } 

            auto left2(-c.imag() >= viewbox.x - viewbox.w / 2); 
            auto right2(-c.imag() <= viewbox.x + viewbox.w / 2);

            if (left2 && right2) 
            {
              auto pos2(to_screen_coords(conj(c)));
              counters[pos2.x()][pos2.y()] += 1;
            }
          }
        }
        break;
      }
    }

    if (i % 1000000 == 0)
    {
      auto percent_complete(i / (double)num_points * 100);
      cout << percent_complete << "% : " << get_max_count() << endl;
    }
  }
}

