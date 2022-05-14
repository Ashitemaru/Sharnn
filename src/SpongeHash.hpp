#pragma once

#include <type_traits>

#include "Bitset.hpp"
#include "PaddedStream.hpp"

template <int r, int c, int o>
class SpongeHash {
public:
    // Refer to the paper for what these abbreviations mean.
    using HM_t = Bitset<r + c>;
    using Z_t = Bitset<r>;
    using Out_t = Bitset<o>;

    // Initialization Vector
    explicit SpongeHash(HM_t IV) : IV(IV) {
    }

    virtual ~SpongeHash() = default;

    virtual HM_t sponge_F(HM_t &h, uint32_t km) = 0;

    Out_t hash(PaddedStream &input) {
        assert(input.get_block_size() == r);
        HM = IV;
        block_count = 0;

        // Absorbing
        bool finished;
        do {
            finished = input.next_block(MB.ptr());
            uint32_t km = block_count == 0 ? 2333 : HM.lsb() + 1;
            HM ^= MB;
            HM = sponge_F(HM, km);
            ++block_count;
        } while (!finished);

        // Squeezing
        Out_t output;
        int out_len = 0;
        do {
            int copy_len = std::min(r, o - out_len);
            std::copy(HM.ptr(), HM.ptr() + copy_len, output.ptr() + out_len);
            uint32_t km = HM.lsb() + 1;
            HM = sponge_F(HM, km);
            out_len += copy_len;
        } while (out_len < o);

        return output;
    }

private:
    HM_t HM{}, IV, MB{};
    int block_count = 0;
};