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

int main() {
    // Unit 0: Basic Hash
    //    std::stringstream ss;
    //    generate_string(ss, 256);
    //    RNNHash rnn_hash;
    //    PaddedStream input_stream{ss, 136};
    //
    //    auto out = rnn_hash.hash(input_stream);
    //    std::cout << out.to_hex_string() << std::endl;

    // Unit 1: Chaotic System
    //    DSTChaoticSystem cs{0x789ABCDF, 233, 0x10, 10};
    //    for (int i = 0; i < 300; i++) {
    //        for (int j = 0; j < 20; j++) {
    //            std::cout << cs.next() << ", ";
    //        }
    //        std::cout << std::endl;
    //    }

    // Unit 2: Sensitivity
    //    for (int i = 0; i < 10; i++) {
    //        std::stringstream ss;
    //        for (int j = 0; j < 300; j++) {
    //            ss << "00000";
    //        }
    //        ss << i;
    //        PaddedStream input_stream{ss, 136};
    //        RNNHash rnn_hash;
    //        auto out = rnn_hash.hash(input_stream);
    //        std::cout << i << ": " << out.to_hex_string() << std::endl;
    //    }

    // Unit 3: Performance
    const int test_size = 1 << 23;  // 8MB

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 256);
    std::stringstream ss;
    for (int i = 0; i < test_size; ++i) {
        ss << (char) dist(rng);
    }

    PaddedStream input_stream{ss, 136};
    RNNHash rnn_hash;

    std::chrono::steady_clock::time_point begin =
        std::chrono::steady_clock::now();
    auto out = rnn_hash.hash(input_stream);
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();

    std::cout << "Hash = " << out.to_hex_string() << std::endl;
    uint64_t time =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
            .count();
    std::cout << "Elapsed Time = " << time << "[ms]" << std::endl;
    double speed = 8.0 * test_size / time * 1000 / (1 << 20);
    std::cout << "Performance = " << speed << "Mbps" << std::endl;
}