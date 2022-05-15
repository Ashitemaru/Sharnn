#include <iostream>
#include <fstream>

#include "../src/RNNHash.hpp"
#include "../include/define.h"

const int k = 21;
const int delta = 1 << (32 - k);

int main() {
    int val {0};
    std::ofstream f {"test.out"};
    auto p {(char *) &val};
    for (int i = 0; i < 1; ++i) {
        std::stringstream s;
        s << p[0] << p[1] << p[2] << p[3];
        f << s.str();
        val += delta;
    }
    f << std::endl;
}
