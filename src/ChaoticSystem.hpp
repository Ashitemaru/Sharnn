#include "ChaoticMap.hpp"

class ChaoticSystem {
public:
    virtual int next() = 0;
};

class DSTChaoticSystem : public ChaoticSystem {
    uint32_t q, ks, kss;
    DSTmap<32> dst;

public:
    DSTChaoticSystem(uint32_t q, uint32_t k0, uint32_t ks, uint32_t us)
        : q(q), ks(ks), kss(k0) {
        while (us--) {
            kss = dst(kss * ks, q);
        }
    }
    int next() override {
        return kss = dst(kss * ks, q);
    }
};
