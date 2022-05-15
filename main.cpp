#include "src/RNNHash.hpp"


void print_usage() {
    std::cout << "Wrong parameters! Example Usage:\n";
    std::cout << "    (1) ./SHA-RNN\n";
    std::cout << "    (2) ./SHA-RNN [-f <file_path>]\n";
    std::cout << "    (3) ./SHA-RNN [-s <string>]\n";
}

int main(int argc, char **argv) {
    RNNHash::Out_t out;
    RNNHash rnn_hash;

    if (argc == 1) {
        std::cout << "You are entering input mode! After you finished inputting, press ^D to exit!\n";
        out = rnn_hash(std::cin);
    } else if (argc == 3) {
        if (strcmp(argv[1], "-f") == 0) {
            std::ifstream file{argv[2], std::ios::binary};
            out = rnn_hash(file);
        } else if (strcmp(argv[1], "-s") == 0) {
            std::istringstream str{argv[2]};
            out = rnn_hash(str);
        } else {
            print_usage();
            return -1;
        }
    } else {
        print_usage();
        return -1;
    }

    auto perf = rnn_hash.last_perf_info();
    std::cout << "Hash = " << out.to_hex_string() << std::endl;
    std::cout << "Size = " << perf.size << " bytes (after padding)" << std::endl;
    if(argc == 3) {
        std::cout << "Time = " << perf.time << " ms" << std::endl;
        std::cout << "Speed = " << perf.speed << " Mbps" << std::endl;
    }
}