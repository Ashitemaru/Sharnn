#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <iostream>

#include "../src/RNNHash.hpp"
#include "../src/define.h"

int main() {
    std::ifstream s {"test.in", std::ifstream::binary};
    std::ofstream record {"diffusion.out"};
    std::stringstream input;
    std::size_t len;

    if (!s.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return 1;
    }

    input.seekg(std::ios::beg);
    PaddedStream p {input, block_size};
    RNNHash hash;
    auto out = hash.hash(p);
    record << out.to_binary_string() << std::endl;

    // input << s.rdbuf();
    // s.seekg(0, std::ios::end);
    // len = s.tellg();
    // s.seekg(0, std::ios::beg);

    // std::random_device dev;
    // std::mt19937 rng(dev());
    // std::uniform_int_distribution<std::mt19937::result_type> byte_dist(0, len - 1);
    // std::uniform_int_distribution<std::mt19937::result_type> bit_dist(0, 7);
    
    // PaddedStream p {input, block_size};
    //     RNNHash hash;
    //     auto out = hash.hash(p);
    //     record << out.to_binary_string() << std::endl;

    // auto flip = [&input, &rng, &byte_dist, &bit_dist] (std::size_t byte, std::size_t bit) {
    //     unsigned char byte_buf;
    //     uint32_t rn;
    //     rn = byte_dist(rng);
    //     input.seekp(rn);
    //     input.seekg(rn);
    //     std:: cerr <<rn << std::endl;
    //     rn = bit_dist(rng);
    //     std:: cerr <<rn << std::endl;
    //     input.read((char *) &byte_buf, 1);
    //     std::cerr << std::hex << (int) byte_buf << std::endl;
    //     byte_buf = ~ (byte_buf | (0xff ^ (1 << rn))) | (byte_buf & (0xff ^ (1 << rn)));
    //     input.write((char *) &byte_buf, 1);
    //     std::cerr << std::hex << (int) byte_buf << std::endl;
    //     input.seekg(std::ios::beg);
    //     input.seekp(std::ios::beg);
    // };

    
    // for (int i = 0; i < filp_count; ++i) {
    //     input.seekg(std::ios::beg);
    //     PaddedStream p {input, block_size};
    //     RNNHash hash;
    //     auto out = hash.hash(p);
    //     record << out.to_binary_string() << std::endl;
    // }
    return 0;
}