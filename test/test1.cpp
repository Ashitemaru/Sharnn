#include "../include/define.h"
#include "../src/RNNHash.hpp"

void generate_string(std::stringstream &ss, int n) {
    ss << std::hex;
    for (int i = 0; i < n; i++) {
        ss << std::setfill('0') << std::setw(2) << i;
    }
}

// Basic Usage
int main() {
    std::stringstream ss;
    generate_string(ss, 256);
    RNNHash rnn_hash;

    auto out = rnn_hash(ss);
    std::cout << out.to_hex_string() << std::endl;
}