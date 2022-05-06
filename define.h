#pragma once

#define DEBUG

#include <cstdint>
#include <cstring>
#include <cassert>
#include <string>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

#define MAX_READ_IN_LEN 65536 // In bytes.
#define HASH_OUT_LEN 80  // In bits.
#define R 16  // In bits.
#define C 64  // In bits.