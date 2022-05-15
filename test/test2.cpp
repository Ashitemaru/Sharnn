#include <chrono>
#include <iostream>
#include <random>
#include <sstream>

#include "RNNHash.hpp"

void generate_string(std::stringstream &ss, int n) {
    ss << std::hex;
    for (int i = 0; i < n; i++) {
        ss << std::setfill('0') << std::setw(2) << i;
    }
}

RNNHash::Out_t out1, out2;

// Consistency Test
int main() {
    std::stringstream ss;
    for (int i = 0; i < 64; i++)
        generate_string(ss, 256);
    std::string str = ss.str();
    RNNHash rnn_hash;

    std::stringstream input{str};
    out1 = rnn_hash(input);
    for (int i = 0; i < 64; i++) {
        std::stringstream input{str};
        out2 = rnn_hash(input);
        if (out1 != out2) {
            std::cerr << "Test Failed" << std::endl;
            return -1;
        }
    }
    std::cout << "Test Pass" << std::endl;
    std::cout << out1.to_hex_string() << std::endl;
}