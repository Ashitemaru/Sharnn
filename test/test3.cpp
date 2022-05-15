#include <random>

#include "RNNHash.hpp"

void generate(std::stringstream &ss, uint64_t size) {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist(0,
                                                                         256);
    for (uint64_t i = 0; i < size; ++i) {
        ss << (char) dist(rng);
    }
}

// Performance Test
int main() {
    const uint64_t size_min = 1LL << 20, size_max = 1LL << 32;  // 1 MB - 4GB
    for (uint64_t size = size_min; size <= size_max; size <<= 1) {
        std::stringstream ss;
        generate(ss, size);

        RNNHash hash;
        RNNHash::Out_t out = hash(ss);
        RNNHash::PerfInfo perf = hash.last_perf_info();

        std::cout << "Hash = " << out.to_hex_string() << std::endl;
        std::cout << "Size = " << perf.size << " bytes" << std::endl;
        std::cout << "Time = " << perf.time << " ms" << std::endl;
        std::cout << "Speed = " << perf.speed << " Mbps" << std::endl
                  << std::endl;
    }
}