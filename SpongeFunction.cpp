//
// Created by c7w on 2022/5/1.
//

#include "SpongeFunction.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include <iostream>

// Params:
// input: The input data.
// input_len: The length of the input data in bytes.
void SpongeFunction::Absorb(const uint8_t* input, uint64_t input_len) {
    assert(input_len % (R >> 3) == 0);

    // XOR the input into the state.
    for (uint64_t i = 0; i < input_len / (R >> 3); i++) {
        for(int j = 0; j < (R >> 3); j++) {
            state[j] ^= input[i * (R >> 3) + j];
        }

        // Call the sponge function.
        F(state, R + C);

        // Print the state in hex.
//        std::stringstream ss;
//        ss << std::hex << std::setfill('0');
//        for (int j = 0; j < (R >> 3); j++) {
//            ss << std::setw(2) << (int)state[j];
//        }
//        ss << " ";
//        for (int j = 0; j < (C >> 3); j++) {
//            ss << std::setw(2) << (int)state[j + (R >> 3)];
//        }
//        std::cout << ss.str() << std::endl;
    }
}

std::string SpongeFunction::Squeeze() {

    assert(HASH_OUT_LEN % R == 0);

    std::stringstream ss;

    // Copy R to output
    while(ss.str().length() < (HASH_OUT_LEN >> 2)) {

        for(int i = 0; i < (R >> 3); i++) {
            ss << std::hex << std::setfill('0') << std::setw(2) << (int)state[i];
        }

        F(state, R + C);
    }

    return ss.str();
}