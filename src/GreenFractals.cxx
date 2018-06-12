#include "GreenFractals.h"

using namespace Eigen;
using namespace Magick;
using namespace std;

GreenFractals::GreenFractals()
  : RNG(
      static_cast<unsigned int>(
        chrono::high_resolution_clock::now().time_since_epoch().count()
      )
    )
{
  auto theta(0.0);
  auto delta(1e-2);
  auto offset(2 * M_PI / 3);
  
  Vector3f axis1(1, 1, 0);
  Vector3f axis2(0, 1, 1);
  Vector3f axis3(1, 0, 1);
  
  Vector3f vec(0, 0, 1);
  auto vec1(vec), vec2(vec), vec3(vec);
  Vector3f hue(1.00, 1.00, 1.00);
  
  axis1.normalize();
  axis2.normalize();
  axis3.normalize();

  for (auto frame(0); frame < NUM_FRAMES; ++frame)
  {
    fill_counters(ch1_counters, 100, 1.0, vec1.x(), vec1.y(), vec1.z());
    fill_counters(ch2_counters, 100, 1.0, vec2.x(), vec2.y(), vec2.z());
    fill_counters(ch3_counters, 100, 1.0, vec3.x(), vec3.y(), vec3.z());
    
    auto ch1_max(get_max_count(ch1_counters));
    auto ch2_max(get_max_count(ch2_counters));
    auto ch3_max(get_max_count(ch3_counters));
    
    for (auto x(0); x < SCREEN_SIZE; ++x)
    {
      for (auto y(0); y < SCREEN_SIZE; ++y)
      {
        auto ch1_value((double)ch1_counters[x][y] / ch1_max);
        auto ch2_value((double)ch2_counters[x][y] / ch2_max);
        auto ch3_value((double)ch3_counters[x][y] / ch3_max);
        
        pixels[3 * (x + y * SCREEN_SIZE) + 0] = hue[0] * ch1_value;
        pixels[3 * (x + y * SCREEN_SIZE) + 1] = hue[1] * ch2_value;
        pixels[3 * (x + y * SCREEN_SIZE) + 2] = hue[2] * ch3_value;
      }
    }
    
    theta += delta;
    
    auto t1(AngleAxis<float>(theta +  0 * offset, axis1));
    auto t2(AngleAxis<float>(theta +  0 * offset, axis2));
    auto t3(AngleAxis<float>(theta +  0 * offset, axis3));
    
    vec1 = t1 * vec;
    vec2 = t2 * vec;
    vec3 = t3 * vec;
    
    ostringstream pathstream;
    pathstream << "frame" << std::setfill('0') << std::setw(4) << frame << ".jpg";
    
    Image image(SCREEN_SIZE, SCREEN_SIZE, "RGB", DoublePixel, &pixels);
    image.write(pathstream.str());
  }
}

Vector2d GreenFractals::to_screen_coords(complex<double> c)
{
  return {
    CONVERSION_FACTOR * c.real() + SCREEN_SIZE / 2,
    CONVERSION_FACTOR * c.imag() + SCREEN_SIZE / 2
  };
}


double GreenFractals::get_max_count(CounterArray& counters)
{
  auto max_count(0);
  
  for (const auto& row : counters)
    for (const auto& count : row)
      if (count > max_count) max_count = count;
  
  return max_count;
}


void GreenFractals::fill_counters(
  CounterArray& counters, 
  unsigned int iterations, double escape_radius, 
  double p, double q, double r)
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
      
      z = p * pow(w, 6) + q * pow(w, 4) + r * pow(w, 2) + C;
      
      path.push_back(z);
      
      if (abs(z) > escape_radius)
      {
        for (auto c : path)
        {
          auto pos1(to_screen_coords(c));
          auto in_bounds(
            pos1.x() > 0 && pos1.y() > 0 &&
            pos1.x() < SCREEN_SIZE && pos1.y() < SCREEN_SIZE
          );
          
          if (in_bounds)
          {
            auto pos2(to_screen_coords({ c.real(),-c.imag()}));
            auto pos3(to_screen_coords({-c.real(), c.imag()}));
            auto pos4(to_screen_coords({-c.real(),-c.imag()}));

            counters[pos1.y()][pos1.x()] += 1;
            counters[pos2.y()][pos2.x()] += 1;
            counters[pos3.y()][pos3.x()] += 1;
            counters[pos4.y()][pos4.x()] += 1;
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
  GreenFractals green_fractals;
}
