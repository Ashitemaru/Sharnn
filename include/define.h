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
#include <chrono>

#define MAX_READ_IN_LEN 65536  // In bytes.
#define HASH_OUT_LEN 80        // In bits.
#define R 16                   // In bits.
#define C 64                   // In bits.

using byte = uint8_t;
