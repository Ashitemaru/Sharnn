#pragma once

#include "NonLinear.hpp"
#include "RNN.hpp"
#include "SpongeHash.hpp"



class RNNHash : public SpongeHash<136, 64, 200> {
public:
    RNNHash() : SpongeHash(HM_t{}) {
    }
    ~RNNHash() override = default;
    void sponge_F(HM_t &h, uint32_t km) override {
        DSTChaoticSystem cs(cs_q, km, cs_ks, cs_us);
        RNN<200> rnn{&cs};
        NonLinear<10, 50> nl{nl_nr};

        rnn.forward(h, wo);

        shift(wo, 24, 40);

        nl.forward(wo, out);

        for (int i = 0; i < 50; i++) {
            h.ptr()[i * 4 + 0] = (out[i] & 0xFF000000) >> 24;
            h.ptr()[i * 4 + 1] = (out[i] & 0x00FF0000) >> 16;
            h.ptr()[i * 4 + 2] = (out[i] & 0x0000FF00) >> 8;
            h.ptr()[i * 4 + 3] = (out[i] & 0x000000FF);
        }
    }

private:
    const static uint32_t cs_q = 19260817, cs_ks = 0x10, cs_us = 10,
                          nl_nr = 8;
    uint32_t wo[10]{}, out[50]{};


    static void shift(uint32_t *d, int length, int total_length) {

        uint8_t t[200];
        for (int i = 0; i < 50; i++) {
            t[i * 4 + 0] = (d[i] & 0xFF000000) >> 24;
            t[i * 4 + 1] = (d[i] & 0x00FF0000) >> 16;
            t[i * 4 + 2] = (d[i] & 0x0000FF00) >> 8;
            t[i * 4 + 3] = (d[i] & 0x000000FF);
        }

        uint8_t tmp[200];
        for(int i = 0; i < total_length - length; ++i) {
            tmp[i] = t[i + length];
        }
        for(int i = 0; i < length; ++i) {
            tmp[i + total_length - length] = t[i];
        }

        for(int i = 0; i < 50; ++i) {
            d[i] = ((uint32_t)tmp[i * 4 + 0] << 24) |
                    ((uint32_t)tmp[i * 4 + 1] << 16) |
                    ((uint32_t)tmp[i * 4 + 2] << 8) |
                   (uint32_t)tmp[i * 4 + 3];
        }
    }
};