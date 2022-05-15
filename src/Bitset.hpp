#pragma once
#include <bitset>
#include <cstdint>
#include <iomanip>
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
        std::fill_n(data, n, filled_with);
    }

    Bitset(const byte *input, int k) {
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

    Bitset(const Bitset<n> &other) : Bitset(other.ptr(), n) {
    }

    Bitset<n> &operator=(const Bitset<n> &other) {
        if (data != other.data) {
            std::copy_n(other.data, n, data);
        }
        return *this;
    }

    byte *ptr() {
        return data;
    }

    const byte *ptr() const {
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

    bool operator==(const Bitset<n> &other) {
        for (int i = 0; i < n; i++) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Bitset<n> &other) {
        return !(*this == other);
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
            ss << std::setfill('0') << std::setw(2) << (uint32_t) data[i];
        }
        return ss.str();
    }

    std::string to_bytes() {
        std::string ret;
        ret.insert(0, (char *)data, n);
        return ret;
    }

    std::size_t one_count() {
        std::size_t count {0};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 7; j++) {
                if (data[i] & (1 << j)) count++;
            }
        }
        return count;
    }

private:
    byte data[n]{};
    void init_with(const byte *input, int k) {
        int len = std::min(k, n);
        std::copy(input, input + len, data);
        std::fill(data + len, data + n, 0);
    }
};