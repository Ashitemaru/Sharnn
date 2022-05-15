#include <iostream>
#include <fstream>

#include "../src/RNNHash.hpp"
#include "defines.h"

const int k = 21;
const int delta = 1 << (32 - k);

int main() {
    std::size_t val {0};
    std::ofstream f {"sample.out"};
    auto p {(char *) &val};
    for (int i = 0; i < (1 << k); ++i) {
        std::stringstream s;
        s << p[0] << p[1] << p[2] << p[3];
        RNNHash rnn_hash;
        auto out = rnn_hash(s);
        f << out.to_bytes();
        val += delta;
    }
}
