#pragma once

#include "../include/define.h"
#include "Bitset.hpp"
#include "ChaoticSystem.hpp"

template <int b, typename std::enable_if<b % 20 == 0, bool>::type = true>
class RNN {
public:
    static constexpr int NEURON_N = b / 20;
    explicit RNN(ChaoticSystem *cs) : cs(cs) {
    }

    void forward(Bitset<b> &input, uint32_t *output) {
        uint32_t msg[5], prev = cs->next();
        for (int i = 0; i < NEURON_N; i++) {
            for (int j = 0; j < 20; j++) {
                msg[j >> 2] = (msg[j >> 2] << 8) | input.ptr()[20 * i + j];
            }
            prev = output[i] = neuron(msg, prev, cs->next(), cs->next());
        }
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

        for (int i = 0; i < ITER_N; i++) {
            f1 = dst(f1, q_dst);
        }
        for (int i = 0; i < ITER_N; i++) {
            f2 = dpwlc(f2, q_dpwlc);
        }

        uint64_t out = f1 ^ f2;

        return f1 ^ f2;
    }
};
