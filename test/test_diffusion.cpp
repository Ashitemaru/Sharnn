#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <iostream>
#include <algorithm>

#include "RNNHash.hpp"
#include "define.h"

const int flip_count {10000};


void flip_test() {
    std::ifstream s {"text.in", std::ifstream::binary};
    std::ofstream record {"diffusion.out"};
    std::stringstream ssbuf;
    ssbuf << s.rdbuf();
    auto stream {ssbuf.str()};

    auto buf = new byte[stream.size()];
    std::copy(stream.begin(), stream.end(), buf);
    std::cerr << buf << std::endl;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> byte_dist(0, stream.size() - 1);
    std::uniform_int_distribution<std::mt19937::result_type> bit_dist(0, 7);
    
    RNNHash h;
    RNNHash::Out_t original = h(ssbuf);
    // record << stream << std::endl;
    // record << original.to_binary_string() << std::endl << std::endl;


    for (int i = 0; i < flip_count; i++) {
        auto bit_r {bit_dist(rng)};
        auto byte_r {byte_dist(rng)};
        auto byte_buf = buf + byte_r;

        *byte_buf = ~ ((*byte_buf) | (0xff ^ (1 << bit_r))) | ((*byte_buf) & (0xff ^ (1 << bit_r)));
        
        std::stringstream input;
        std::string new_stream {(char *)buf};
        input.str(new_stream);

        RNNHash hash;
        RNNHash::Out_t out = hash(input);
        // std::cerr << new_stream << std::endl;
        // record << "flip byte: " << byte_r << "; bit: " << bit_r << std::endl;
        // record << out.to_binary_string() << std::endl;
        out ^= original;
        record << out.one_count() << std::endl;
        // if (out.one_count() == 0) {
        //     std::fstream opt {"1.bin"};
        //     std::ofstream ori{"2.bin"};
        //     opt  << new_stream << std::endl;
        //     ori  << stream << std::endl;
        //     exit(0);
        // }

        *byte_buf = ~ ((*byte_buf) | (0xff ^ (1 << bit_r))) | ((*byte_buf) & (0xff ^ (1 << bit_r)));
    }
    
}

int main() {
    
    flip_test();      
        
    return 0;
}