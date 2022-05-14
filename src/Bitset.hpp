#include <bitset>
#include <cstdint>
#include <sstream>
using byte = uint8_t;

#ifdef _MSC_VER
#include <intrin.h>

uint32_t __inline ctz(uint32_t value) {
    DWORD trailing_zero = 0;
    _BitScanForward(&trailing_zero, value);
    return trailing_zero;
}
#else
#define ctz(x) __builtin_ctz(x)
#endif

// Replacement of std::bitset
// More convenient API and todo SIMD optimization
template <int n>
class Bitset {
public:
    Bitset() : Bitset(0) {
    }

    explicit Bitset(int filled_with) {
        std::fill(data, data + n, filled_with);
    }

    Bitset(byte *input, int k) {
        init_with(input, k);
    }

    template <int k>
    explicit Bitset(const Bitset<k> &other) : Bitset(other.ptr(), k) {
    }

    template <int k>
    Bitset &operator=(const Bitset<k> &other) {
        if (this != &other) {
            init_with(other.data, k);
        }
        return *this;
    }

    byte *ptr() {
        return data;
    }

    Bitset &operator|=(const Bitset<n> &other) {
        for (int i = 0; i < n; i++) {
            data[i] |= other.data[i];
        }
        return *this;
    }

    Bitset &operator&=(const Bitset<n> &other) {
        for (int i = 0; i < n; i++) {
            data[i] &= other.data[i];
        }
        return *this;
    }

    Bitset &operator^=(const Bitset<n> &other) {
        for (int i = 0; i < n; i++) {
            data[i] ^= other.data[i];
        }
        return *this;
    }

    Bitset &operator!() {
        for (int i = 0; i < n; i++) {
            data[i] = ~data[i];
        }
        return *this;
    }

    // least significant bit
    int lsb() {
        int ans = 0;
        for (int i = n - 1; i >= 0; i++) {
            if (data[i] == 0) {
                ans += 8;
            } else {
                ans += ctz(data[i]);
                return ans;
            }
        }
        return ans;
    }

    std::string to_binary_string() {
        std::stringstream ss;
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                ss << ' ';
            }
            ss << std::bitset<8>(data[i]);
        }
        return ss.str();
    }

    std::string to_hex_string() {
        std::stringstream ss;
        ss << std::hex;
        for (int i = 0; i < n; i++) {
            ss << data[i];
        }
        return ss.str();
    }

private:
    byte data[n]{};
    void init_with(byte *input, int k) {
        int len = std::min(k, n);
        std::copy(input, input + len, data);
        std::fill(data + len, data + n, 0);
    }
};