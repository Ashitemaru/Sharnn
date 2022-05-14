#pragma once

// Discrete Skew Tent map
template <int N>
class DSTmap {
    const uint64_t twoN = 1LL << N;

public:
    uint32_t operator()(uint32_t ks, uint32_t q) {
        uint64_t x = ks;

        assert(0 < q && q < twoN);
        assert(0 < x && x < twoN);

        if (x < q) {
            return (x << N) / q;
        } else if (x == q) {
            return twoN - 1;
        } else if (x < twoN) {
            return ((twoN - ks) << N) / (twoN - q);
        }

        return 0;
    }
};

// Discrete Piecewise Linear Chaotic map
template <int N>
class DPWLCmap {
    const uint64_t twoN = 1LL << N;
    const uint64_t twoN_1 = 1LL << (N - 1);

public:
    uint32_t operator()(uint32_t ks, uint32_t q) {
        uint64_t x = ks;

        q %= twoN_1;
        if (x <= q) {
            return (x << N) / q;
        } else if (x <= twoN_1) {
            return ((x - q) << N) / (twoN_1 - q);
        } else if (x <= twoN - q) {
            return ((twoN - x - q) << N) / (twoN_1 - q);
        } else if (x <= twoN - 1) {
            return ((twoN - x) << N) / q;
        } else {
            return twoN - 1 - q;
        }
    }
};