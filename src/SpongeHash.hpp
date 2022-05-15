#pragma once

<<<<<<< HEAD
#include "../include/define.h"
=======
#include <chrono>
#include <type_traits>

>>>>>>> origin/master
#include "Bitset.hpp"
#include "PaddedStream.hpp"

#ifndef NDEBUG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG
#endif

template <int r, int c, int o>
class SpongeHash {
public:
    // Refer to the paper for what these abbreviations mean.
    using HM_t = Bitset<r + c>;
    using Z_t = Bitset<r>;
    using Out_t = Bitset<o>;

    struct PerfInfo {
        // Byte, Ms, Mbps
        uint64_t size, time;
        double speed;
    };

    // Initialization Vector
    explicit SpongeHash(HM_t IV) : IV(IV) {
    }

    virtual ~SpongeHash() = default;

    virtual void sponge_F(HM_t &h, uint32_t km) = 0;

    Out_t operator()(std::istream &input) {
        return hash(input);
    }

    Out_t hash(std::istream &input) {
        last_perf.size = 0;
        std::chrono::steady_clock::time_point begin =
            std::chrono::steady_clock::now();

        PaddedStream stream{input, r};
        HM = IV;

        // Absorbing
        bool finished;
        do {
            finished = stream.next_block(MB.ptr());
            uint32_t km = last_perf.size == 0 ? 2333 : HM.lsb() + 1;
            HM ^= MB;
            sponge_F(HM, km);
            last_perf.size += r;
        } while (!finished);

        // Squeezing
        Out_t output;
        int out_len = 0;
        do {
            int copy_len = std::min(r, o - out_len);
            std::copy(HM.ptr(), HM.ptr() + copy_len, output.ptr() + out_len);
            uint32_t km = HM.lsb() + 1;
            sponge_F(HM, km);
            out_len += copy_len;
        } while (out_len < o);

        std::chrono::steady_clock::time_point end =
            std::chrono::steady_clock::now();
        last_perf.time =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
                .count();
        last_perf.speed =
            (8000.0 * last_perf.size) / (last_perf.time * 1048576);

        return output;
    }

    PerfInfo last_perf_info() {
        return last_perf;
    }

private:
    HM_t HM{}, IV, MB{};
    PerfInfo last_perf{};
};