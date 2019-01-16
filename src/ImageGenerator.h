#ifndef IMAGE_GENERATOR_H
#define IMAGE_GENERATOR_H

#include <array>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

#include <Magick++.h>

#include "Constants.h"
#include "FractalInstance.h"

using namespace std;

class ImageGenerator
{
public:
  static void generate(FractalInstance& fi, unsigned frame = 0)
  {
    auto max(fi.get_max_count());
    double* pixels = new double[3 * SCREEN_SIZE * SCREEN_SIZE];

    for (auto x(0); x < SCREEN_SIZE; ++x)
    {
      for (auto y(0); y < SCREEN_SIZE; ++y)
      {
        auto value((double)fi.counters[x][y] / max);

        pixels[3 * (x + y * SCREEN_SIZE) + 0] = fi.get_hue()[0] * value;
        pixels[3 * (x + y * SCREEN_SIZE) + 1] = fi.get_hue()[1] * value;
        pixels[3 * (x + y * SCREEN_SIZE) + 2] = fi.get_hue()[2] * value;
      }
    }

    ostringstream pathstream;

    if (frame == 0)
    {
      pathstream << "images/green-fractal-" << time(nullptr) << ".jpg";
    } else {
      pathstream << "frames/frame" << setfill('0') << setw(4) << frame << ".jpg";
    }

    Image image(SCREEN_SIZE, SCREEN_SIZE, "RGB", DoublePixel, pixels);
    image.write(pathstream.str());

    delete[] pixels;
  }

  static void generate(vector<FractalInstance> fis, unsigned frame = 0)
  {
    auto r_max(fis[0].get_max_count());
    auto g_max(fis[0].get_max_count());
    auto b_max(fis[0].get_max_count());
    double* pixels = new double[3 * SCREEN_SIZE * SCREEN_SIZE];

    for (auto x(0); x < SCREEN_SIZE; ++x)
    {
      for (auto y(0); y < SCREEN_SIZE; ++y)
      {
        auto r_value((double)fis[0].counters[x][y] / r_max);
        auto g_value((double)fis[1].counters[x][y] / g_max);
        auto b_value((double)fis[2].counters[x][y] / b_max);

        pixels[3 * (x + y * SCREEN_SIZE) + 0] = r_value;
        pixels[3 * (x + y * SCREEN_SIZE) + 1] = g_value;
        pixels[3 * (x + y * SCREEN_SIZE) + 2] = b_value;
      }
    }

    ostringstream pathstream;

    if (frame == 0)
    {
      pathstream << "images/green-fractal-" << time(nullptr) << ".jpg";
    } else {
      pathstream << "frames/frame" << setfill('0') << setw(4) << frame << ".jpg";
    }

    Image image(SCREEN_SIZE, SCREEN_SIZE, "RGB", DoublePixel, pixels);
    image.write(pathstream.str());

    delete[] pixels;
  }

};

#endif // IMAGE_GENERATOR_H
