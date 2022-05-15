#include "src/RNNHash.hpp"

int main(int argc, char **argv) {
    RNNHash::Out_t out;
    RNNHash rnn_hash;

    if (argc == 1) {
        out = rnn_hash(std::cin);
    } else if (argc == 3) {
        if (strcmp(argv[1], "-f") == 0) {
            std::ifstream file{argv[2], std::ios::binary};
            out = rnn_hash(file);
        } else if (strcmp(argv[1], "-s") == 0) {
            std::istringstream str{argv[2]};
            out = rnn_hash(str);
        } else {
            return -1;
        }
    } else {
        return -1;
    }

    auto perf = rnn_hash.last_perf_info();
    std::cout << "Hash = " << out.to_hex_string() << std::endl;
    std::cout << "Size = " << perf.size << " bytes" << std::endl;
    std::cout << "Time = " << perf.time << " ms" << std::endl;
    std::cout << "Speed = " << perf.speed << " Mbps" << std::endl;
}