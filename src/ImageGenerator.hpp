#ifndef IMAGE_GENERATOR_H
#define IMAGE_GENERATOR_H

#include <array>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <Magick++.h>

#include "Constants.hpp"
#include "FractalInstance.hpp"


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

        pixels[3 * (x + y * SCREEN_SIZE) + 0] = value;
        pixels[3 * (x + y * SCREEN_SIZE) + 1] = value;
        pixels[3 * (x + y * SCREEN_SIZE) + 2] = value;
      }
    }

    ostringstream pathstream;
    pathstream << "frames/frame" << std::setfill('0') << std::setw(4) << frame << ".jpg";

    Image image(SCREEN_SIZE, SCREEN_SIZE, "RGB", DoublePixel, pixels);
    image.write(pathstream.str());

    delete[] pixels;
  }

};

#endif // IMAGE_GENERATOR_H
