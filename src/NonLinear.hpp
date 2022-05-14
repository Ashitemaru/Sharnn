#pragma once

#include <algorithm>
#include <cstdint>
#include <type_traits>

template <int N, int O, typename std::enable_if<N % 5 == 0, bool>::type = true>
class NonLinear {
public:
    static constexpr int INPUT_N = N / 5;

    explicit NonLinear(int nr) : nr(nr) {
    }

    void forward(uint32_t *input, uint32_t *output) {
        uint32_t h[INPUT_N * 8];
        for (int i = 0; i < INPUT_N; i++) {
            auto i_ptr = input + i * 5, o_ptr = h + i * 8;
            nl_5to8(i_ptr, o_ptr);
            for (int j = 0; j < nr; j++) {
                nl_8to8(o_ptr, o_ptr);
            }
        }
        int out_count = 0;
        while (out_count < O) {
            int count = std::min(O - out_count, INPUT_N * 8);
            std::copy(h, h + count, output);
            output += count;
            out_count += count;
            for (int i = 0; i < INPUT_N; i++) {
                auto h_ptr = h + i * 8;
                nl_8to8(h_ptr, h_ptr);
            }
        }
    }

private:
    int nr;
    void nl_5to8(uint32_t *d, uint32_t *h) {
        uint32_t t = ch(d[1], d[2], d[3]) ^ d[4] ^ sum_1(d[3]);
        h[0] = d[0] ^ t ^ maj(d[1], d[2], d[3]) ^ sum_0(d[1]);
        h[1] = t ^ d[0];
        h[2] = d[0] ^ d[1];
        h[3] = d[1] ^ d[2];
        h[4] = d[2] ^ d[3];
        h[5] = d[0] ^ d[1] ^ t;
        h[6] = d[1] ^ d[2] ^ t;
        h[7] = d[2] ^ d[3] ^ t;
    }
    void nl_8to8(uint32_t *d, uint32_t *h) {
        uint32_t t = d[7] + ch(d[4], d[5], d[6]) + sum_1(d[4]);
        uint32_t a = t + maj(d[0], d[1], d[2]) + sum_0(d[0]);
        h[7] = d[6];
        h[6] = d[5];
        h[5] = d[4];
        h[4] = d[3] + t;
        h[3] = d[2];
        h[2] = d[1];
        h[1] = d[0];
        h[0] = a;
    }
    static uint32_t maj(uint32_t a, uint32_t b, uint32_t c) {
        return (a & b) ^ (b & c) ^ (a & c);
    }
    static uint32_t ch(uint32_t a, uint32_t b, uint32_t c) {
        return (a & b) ^ (~a & c);
    }
    static uint32_t sum_0(uint32_t x) {
        return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
    }
    static uint32_t sum_1(uint32_t x) {
        return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
    }
    static uint32_t rotr(uint32_t x, uint32_t n) {
        return (x >> n) | (x << (32 - n));
    }
};