#pragma once

#include "define.h"
#include "ByteStream.hpp"

class SpongeFunction {
private:
    ByteStream *state;

    ByteStream *pad(ByteStream *input) {
        int len = input->get_length();
        if (len % (R >> 3)) {
            int pad_length = (R >> 3) - len % (R >> 3);
            input->pad(pad_length);
        }
        return input;
    }

    void absorb(ByteStream *input) {
        assert(input->get_length() % (R >> 3) == 0);

        // XOR the input to the state
        int len = input->get_length();
        for (int i = 0; i < len / (R >> 3); ++i) {
            for (int j = 0; j < (R >> 3); ++j)
                state->data[j] ^= input->data[i * (R >> 3) + j];

            F(state);
        }
    }

    std::string squeeze() {
        assert(HASH_OUT_LEN % R == 0);

        // Copy R to output
        std::stringstream ss;
        while (ss.str().length() < (HASH_OUT_LEN >> 2)) {
            for (int i = 0; i < (R >> 3); ++i)
                ss << std::hex << std::setfill('0') << std::setw(2)
                   << (int) state->data[i];

            F(state);
        }

        return ss.str();
    }

    // The compress function, override it to get different Hash
    virtual void F(ByteStream *) = 0;

public:
    explicit SpongeFunction() {
        state = ByteStream::zeros((R + C) >> 3);
    }

    ~SpongeFunction() {
        delete state;
    }

    std::string forward(ByteStream *input) {
        absorb(pad(input));
        return squeeze(); // TODO: is it necessary to clear the state to 0 after one pass?
    }
};