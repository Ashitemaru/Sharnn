#pragma once

#include "define.h"

class BitStream {
private:
    uint8_t *data;
    int length; // @note: Length in BIT
    bool copied; // @note: Whether the BS is constructed by copying bits

    char bits_to_hex_char(int bits) {
        if (bits < 0) assert(false);
        else if (bits < 10) return '0' + bits;
        else if (bits < 16) return 'A' + bits - 10;
        else assert(false);
    }

    /** It will reset remaining bits to 0
     *  when the length is not a multiple of 8
     */
    void reset_remain_bits() {
        int remain_length = length & 0x7;
        for (int shift = remain_length; shift < 8; ++shift)
            data[length >> 3] &= ~(BITMAP_BASE >> shift);
    }

    BitStream(int _length, uint8_t *_data, bool _copied)
        : length(_length), data(_data), copied(_copied) { }

public:
    static BitStream *copy_from(int _length, uint8_t *_data) {
        uint8_t *buf = new uint8_t[(_length >> 3) + 1];
        memcpy(buf, _data, (_length >> 3) + 1);
        BitStream *bs = new BitStream(_length, buf, true);
        bs->reset_remain_bits();
        return bs;
    }

    /** @warn: This function may change several bits in '_data'
     */
    static BitStream *move_from(int _length, uint8_t *_data) {
        BitStream *bs = new BitStream(_length, _data, false);
        bs->reset_remain_bits();
        return bs;
    }

    static BitStream *zeros(int _length) {
        uint8_t *buf = new uint8_t[(_length >> 3) + 1];
        memset(buf, 0, (_length >> 3) + 1);
        return new BitStream(_length, buf, true);
    }

    bool get_bit(int loc) {
        assert(loc >= 0 && loc < length);
        return data[loc >> 3] & (BITMAP_BASE >> (loc & 0x7));
    }

    void set_bit(int loc) {
        assert(loc >= 0 && loc < length);
        data[loc >> 3] |= (BITMAP_BASE >> (loc & 0x7));
    }

    void reset_bit(int loc) {
        assert(loc >= 0 && loc < length);
        data[loc >> 3] &= ~(BITMAP_BASE >> (loc & 0x7));
    }

    std::string hex_string() {
        std::string res = "";
        if (length & 0x3) {
            printf("WARNING: This bitstream will be padded "
                "by zero for its length is not a multiple of 4.\n");
        }

        #define CONV_HI res.push_back(bits_to_hex_char((bits & 0xf0) >> 4))
        #define CONV_LO res.push_back(bits_to_hex_char(bits & 0xf))

        for (int i = 0; i < (length >> 3) + 1; ++i) {
            uint8_t bits = data[i];
            int remain_length = length & 0x7;

            if (!(i == length >> 3 && remain_length == 0)) CONV_HI;
            if (!(i == length >> 3 && remain_length <= 4)) CONV_LO;
        }

        return res;
    }

    ~BitStream() {
        if (copied) delete[] data;
    }
};