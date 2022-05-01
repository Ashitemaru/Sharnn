//
// Created by c7w on 2022/5/1.
//

#ifndef SHARNN_SPONGEFUNCTION_H
#define SHARNN_SPONGEFUNCTION_H

// Maybe moving these macros to `main.cpp` later is a better choice.
#include <cstdint>
#include <string>
#include <cstring>
#include <functional>
#include <utility>

#define HASH_OUT_LEN 80  // In bits.
#define R 16  // In bits.
#define C 64  // In bits.

class SpongeFunction {

private:

    // The state of the sponge function.
    uint8_t* state;
    std::function<void(uint8_t*, uint64_t)> F;



public:
    // Constructor
    explicit SpongeFunction(std::function<void(uint8_t*, uint64_t)> F) {
        state = new uint8_t[(R + C) >> 3];

        // TODO: Initial Value to be 0, safe ???
        memset(state, 0, (R + C) >> 3);
        this->F = std::move(F); // (state, length) => void, where length == R + C
    }

    // Destructor
    ~SpongeFunction() {
        delete[] state;
    }

    // Sponge Functions: Absorbing and Squeezing
    void Absorb(const uint8_t* input, uint64_t input_len);
    std::string Squeeze();
    
};


#endif //SHARNN_SPONGEFUNCTION_H
