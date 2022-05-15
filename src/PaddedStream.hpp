#pragma once

#include "../include/define.h"

// multi-rate padding
class PaddedStream {
public:
    PaddedStream(std::istream &input, int block_size)
        : input(input), block_size(block_size), finished(false) {
    }

    bool next_block(byte *block) {
        if (finished)
            return false;
        input.read(reinterpret_cast<char *>(block), block_size);
        int read_count = input.gcount();
        finished = true;
        if (read_count < block_size - 1) {
            int i = read_count;
            block[i] = 0b01100000;
            for (; i < read_count - 1; ++i) {
                block[i] = 0;
            }
            block[i] = 0b00000001;
        } else if (read_count == block_size - 1) {
            block[read_count] = 0b01100001;
        } else {
            finished = false;
        }
        return finished;
    }

    int get_block_size() const {
        return block_size;
    }

private:
    std::istream &input;
    int block_size;
    bool finished;
};