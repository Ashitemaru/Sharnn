#pragma once

#include "Bitset.hpp"
#include "ChaoticSystem.hpp"
#include "define.h"

#ifndef NDEBUG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG
#endif

template <int b, typename std::enable_if<b % 20 == 0, bool>::type = true>
class RNN {
public:
    static constexpr int NEURON_N = b / 20;
    explicit RNN(ChaoticSystem *cs) : cs(cs) {
    }

    void forward(Bitset<b> &input, uint32_t *output) {
        uint32_t msg[5], prev = 0;
        for (int i = 0; i < NEURON_N; i++) {
            for (int j = 0; j < 20; j++) {
                msg[j >> 2] = (msg[j >> 2] << 8) | input.ptr()[20 * i + j];
            }
            prev = output[i] = neuron(msg, prev, cs->next(), cs->next());
        }
        LOG("RNN Layer output: ");
        for (int i = 0; i < NEURON_N; i++) {
            LOG("%08x ", output[i]);
        }
        LOG("\n");
    }

private:
    const int ITER_N = 20;
    DSTmap<32> dst{};
    DPWLCmap<32> dpwlc{};
    ChaoticSystem *cs;

    uint32_t neuron(uint32_t *msg,
                    uint32_t prev,
                    uint32_t q_dst,
                    uint32_t q_dpwlc) {
        uint32_t f1 = mul(msg[0], cs->next()) + mul(msg[1], cs->next()) +
                      mul(msg[2], cs->next()) + prev;
        uint32_t f2 = mul(msg[3], cs->next()) + mul(msg[4], cs->next()) + prev;
        LOG("Neuron: IN: %08x %08x %08x %08x %08x PREV: %08x F: %08x "
            "%08x\n",
            msg[0],
            msg[1],
            msg[2],
            msg[3],
            msg[4],
            prev,
            f1,
            f2);
        for (int i = 0; i < ITER_N; i++) {
            f1 = dst(f1, q_dst);
        }
        for (int i = 0; i < ITER_N; i++) {
            f2 = dpwlc(f2, q_dpwlc);
        }

        uint64_t out = f1 ^ f2;
        LOG("Neuron: %08x %08x %08x %08x %08x\n", q_dst, f1, q_dpwlc, f2, out);

        return f1 ^ f2;
    }
};