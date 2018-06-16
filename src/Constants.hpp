#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <random>
#include <Eigen/Geometry>
#include <Magick++.h>

constexpr auto COMPLEX_RANGE(3.0);
constexpr auto NUM_POINTS(1.6e6);

constexpr auto NUM_FRAMES(100);
constexpr auto SCREEN_SIZE(1400);
constexpr auto CONVERSION_FACTOR(SCREEN_SIZE / COMPLEX_RANGE);

using namespace std;
using namespace Eigen;
using namespace Magick;

using CounterArray = array<array<int, SCREEN_SIZE>, SCREEN_SIZE>;

static default_random_engine rand_eng;

#endif // CONSTANTS_H
