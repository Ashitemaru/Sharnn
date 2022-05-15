#include <iostream>

#include "../src/RNNHash.hpp"
#include "defines.h"


int main() {
    std::size_t val {9999999999999};
    for (int i = 0; i < 1000000; ++i) {
        std::stringstream s;
        val += 10;
        s << val ;
        PaddedStream p {s, block_size};
        RNNHash H;
        std::cout << H.hash(p).to_bytes();
    }
}