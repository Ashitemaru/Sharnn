#include <type_traits>

#include "Bitset.hpp"

template <int r,
          int c,
          int o,
          typename std::enable_if<o % r == 0, bool>::type = true>
class SpongeHash {
public:
    // Refer to the paper for what these abbreviations mean.
    using HM_t = Bitset<r + c>;
    using Z_t = Bitset<r>;
    using Out_t = Bitset<o>;

    // Initialization Vector
    explicit SpongeHash(HM_t IV) : IV(IV) {
    }

    virtual ~SpongeHash() = 0;

    virtual HM_t sponge_F(HM_t h) = 0;

    Out_t hash(PaddedStream &input) {
        assert(input.get_block_size() == r);
        HM = IV;

        // Absorbing
        bool has_next;
        do {
            has_next = input.next_block(MB.ptr());
            HM ^= MB;
            HM = sponge_F(HM);
        } while (has_next);

        // Squeezing
        Out_t output;
        for (int i = 0; i < o / r; ++i) {
            for (int j = 0; j < r; ++j) {
                output.ptr()[i * r + j] = HM.ptr()[j];
            }
            HM = sponge_F(HM);
        }

        return output;
    }

private:
    HM_t HM{}, IV, MB{};
};