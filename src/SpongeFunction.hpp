#pragma once

#include <chrono>

#include "ByteStream.hpp"
#include "define.h"

class SpongeFunction {
private:
    /** @note: 'state' & these functions are all private,
     *         even not visible to derived classes
     */
    ByteStream *state;

    ByteStream *pad(ByteStream *input) {
        int len = input->get_length();
        if (len % (R >> 3)) {
            int pad_length = (R >> 3) - len % (R >> 3);
            input->pad(pad_length);
        }
        return input;
    }

    /** @note: The compress function, override it to get different HASH
     *  @param: A pointer to the state, you should convert the old data it
     * points to into the new state
     */
    virtual void F(ByteStream *) = 0;

    void wrapped_F() {
        ByteStream *new_state = ByteStream::copy_from(state);
        F(new_state);
        assert(new_state->get_length() == state->get_length());
        delete state;
        state = new_state;
    }

public:
    explicit SpongeFunction() {
        state = ByteStream::zeros((R + C) >> 3);
    }

    virtual ~SpongeFunction() {
        delete state;
    }

    void absorb(ByteStream *input) {
        input = pad(input);

        // XOR the input to the state
        int len = input->get_length();
        for (int i = 0; i < len / (R >> 3); ++i) {
            for (int j = 0; j < (R >> 3); ++j)
                state->data[j] ^= input->data[i * (R >> 3) + j];

#ifdef SAFE_DERIVE
            wrapped_F();  // Compress
#else
            F(state);  // Compress
#endif
        }
    }

    std::string squeeze(int hash_len) {
        assert(HASH_OUT_LEN % R == 0);

        // Copy R to output
        std::stringstream ss;
        while (ss.str().length() < (hash_len >> 2)) {
            for (int i = 0; i < (R >> 3); ++i)
                ss << std::hex << std::setfill('0') << std::setw(2)
                   << (int) state->data[i];

#ifdef SAFE_DERIVE
            wrapped_F();  // Compress
#else
            F(state);  // Compress
#endif
        }

        return ss.str();
    }
};