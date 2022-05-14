#include "ChaoticMap.hpp"

class ChaoticSystem {
public:
    virtual int next() = 0;
};

class DSTChaoticSystem : public ChaoticSystem {
    int kssi = 0;
    int q = 0;
    DSTmap<32> dst;

public:
    DSTChaoticSystem(int q, int k0) : q(q), kssi(k0) {
    }
    virtual int next() override {
        this->kssi = this->dst(this->kssi, this->q);
        return this->kssi;
    }
};
