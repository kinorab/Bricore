#pragma once

#include <cassert>
#include <iostream>
#include <limits>
#include <stdexcept>

extern const size_t startTimeP;

extern const int rng(const int lowerLimit = std::numeric_limits<int>().min(), const int upperLimit = std::numeric_limits<int>().max());
extern const int prng(const int lowerLimit = 0);
extern void getPlayedTime();
