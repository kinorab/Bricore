#pragma once

#include "../common.h"

extern const int rng(const int lowerLimit = std::numeric_limits<int>().min(), const int upperLimit = std::numeric_limits<int>().max());
extern const int prng(const int lowerLimit = 0);