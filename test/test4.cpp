#include <cstdint>
#include <iostream>
#include <random>
#include <streambuf>

#include "RNNHash.hpp"

const int data_size = 1024;
uint8_t ori_data[data_size], data[data_size];

struct membuf : std::streambuf {
    membuf(char *begin, uint32_t size) {
        this->setg(begin, begin, begin + size);
    }
};

uint32_t random_number(uint32_t rand_max) {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist(
        0, 0xFFFFFFFF);
    return dist(rng) % rand_max;
}

void print_data(uint8_t *data) {
    for (int i = 0; i < data_size; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(2)
                  << (uint32_t) data[i];
    }
    std::cout << std::endl;
}

int main() {
    for (uint8_t &i : ori_data) {
        i = random_number(256);
    }

    print_data(ori_data);
    RNNHash::Out_t out1, out2;
    RNNHash h;

    {
        membuf buf{reinterpret_cast<char *>(ori_data), data_size};
        std::istream input(&buf);
        out1 = h(input);
        std::cout << "Hash: " << out1.to_hex_string() << std::endl;
    }

    for (int i = 0; i < 100000; i++) {
        uint32_t pos = random_number(data_size);
        uint32_t bit = random_number(8);
        std::copy_n(ori_data, data_size, data);
        data[pos] ^= 1 << bit;

        membuf buf{reinterpret_cast<char *>(data), data_size};
        std::istream input(&buf);
        out2 = h(input);
        if (out1 == out2) {
            std::cout << std::dec << pos << " " << bit << " : ";
            print_data(data);
            return -1;
        }
    }

    printf("TEST PASS");
}