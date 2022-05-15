#pragma once

#define DEBUG
#define SAFE_DERIVE
#define SIMPLE_ACTIVATE

#include <cassert>
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

#define MAX_READ_IN_LEN 65536  // In bytes.
#define HASH_OUT_LEN 80        // In bits.
#define R 16                   // In bits.
#define C 64                   // In bits.

using byte = uint8_t;

#ifndef NDEBUG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG
#endif

inline uint32_t mul(uint32_t a, uint32_t b) {
    uint64_t r = ((uint64_t) a) * b;
    return r ^ (r >> 32);
}