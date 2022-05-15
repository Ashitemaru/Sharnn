#pragma once

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using byte = uint8_t;

inline uint32_t mul(uint32_t a, uint32_t b) {
    uint64_t r = ((uint64_t) a) * b;
    return r ^ (r >> 32);
}