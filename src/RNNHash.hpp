#pragma once

#include "NonLinear.hpp"
#include "RNN.hpp"
#include "SpongeHash.hpp"

class RNNHash : public SpongeHash<136, 64, 32> {
public:
    RNNHash() : SpongeHash(HM_t{}) {
    }
    ~RNNHash() override = default;
    HM_t sponge_F(HM_t &h, uint32_t km) override {
        DSTChaoticSystem cs(cs_q, km, cs_ks, cs_us);
        RNN<200> rnn{&cs};
        NonLinear<10, 50> nl{nl_nr};
        uint32_t wo[10], out[50];

        rnn.forward(h, wo);
        nl.forward(wo, out);

        HM_t out_hm;
        for (int i = 0; i < 50; i++) {
            out_hm.ptr()[i * 4 + 0] = (out[i] & 0xFF000000) >> 24;
            out_hm.ptr()[i * 4 + 1] = (out[i] & 0x00FF0000) >> 16;
            out_hm.ptr()[i * 4 + 2] = (out[i] & 0x0000FF00) >> 8;
            out_hm.ptr()[i * 4 + 3] = (out[i] & 0x000000FF);
        }
        return out_hm;
    }

private:
    const static uint32_t cs_q = 0x789ABCDE, cs_ks = 0x10, cs_us = 10,
                          nl_nr = 8;
};