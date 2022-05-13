#pragma once

#include "define.h"

class ByteStream {
private:
    int length;
    bool copied;

    inline static void check_positive(int param) {
        if (param <= 0) {
            printf("Bad parameter. Length should be positive.\n");
            assert(false);
        }
    }

    inline static char bits_to_hex_char(int bits) {
        assert(bits >= 0 && bits < 16);
        return bits < 10 ? '0' + bits : 'a' + bits - 10;
    }

    ByteStream(uint8_t *_data, int _length, bool _copied)
        : data(_data), length(_length), copied(_copied) { }

public:
    /** @note: I make it public so that we can use it freely
     */
    uint8_t *data;

    static ByteStream *copy_from_raw(uint8_t *_data, int _length) {
        check_positive(_length);
        uint8_t *buf = new uint8_t[_length];
        memcpy(buf, _data, _length);
        return new ByteStream(buf, _length, true);
    }

    static ByteStream *copy_from(ByteStream *bs) {
        return copy_from_raw(bs->data, bs->length);
    }

    static ByteStream *move_from_raw(uint8_t *_data, int _length) {
        check_positive(_length);
        return new ByteStream(_data, _length, false);
    }

    static ByteStream *zeros(int _length) {
        check_positive(_length);
        uint8_t *buf = new uint8_t[_length];
        memset(buf, 0, _length);
        return new ByteStream(buf, _length, true);
    }

    /** @note: This function will let the BS give up the ownership
     *         of the original data array if the BS is constructed by moving.
     */
    void append(ByteStream *tail) {
        int tail_length = tail->get_length();
        uint8_t *buf = new uint8_t[length + tail_length];
        memcpy(buf, data, length);
        memcpy(buf + length, tail->data, tail_length);

        if (copied) delete[] data;
        else copied = true;

        data = buf;
        length += tail_length;
    }

    /** @note: This function will let the BS give up the ownership
     *         of the original data array if the BS is constructed by moving.
     */
    void pad(int pad_length) {
        check_positive(pad_length);
        ByteStream *pad_tail = ByteStream::zeros(pad_length);
        append(pad_tail);
        delete pad_tail;
    }

    /** @warn: This function will not copy data
     */
    ByteStream *slice(int begin, int slice_len) {
        int clamped_len = begin + slice_len > length ? length - begin : slice_len;
        return ByteStream::move_from_raw(data + begin, clamped_len);
    }

    void clear() { memset(data, 0, length); }

    int get_length() { return length; }

    std::string hex_string() {
        std::string res = "";
        for (int i = 0; i < length; ++i) {
            uint8_t bits = data[i];
            res.push_back(bits_to_hex_char((bits & 0xf0) >> 4));
            res.push_back(bits_to_hex_char(bits & 0xf));
        }
        return res;
    }

    bool operator==(ByteStream &other) {
        if (length != other.get_length()) return false;

        for (int i = 0; i < length; ++i)
            if (data[i] != other.data[i]) return false;

        return true;
    }

    bool operator!=(ByteStream &other) { return !(*this == other); }

    ~ByteStream() {
        if (copied) delete[] data;
    }

    static void test() {
#ifdef DEBUG
        uint8_t data[4] = {0x54, 0x76, 0xa3, 0xff};
        ByteStream *bs_cp = ByteStream::copy_from_raw(data, 3);
        ByteStream *bs_mv = ByteStream::move_from_raw(data, 3);
        ByteStream *zero = ByteStream::zeros(3);
        printf("Construction test passed!\n");

        assert(bs_cp->hex_string() == "5476a3");
        assert(zero->hex_string() == "000000");
        printf("Hex string test passed!\n");

        bs_cp->pad(3);
        assert(bs_cp->get_length() == 6);
        assert(bs_cp->hex_string() == "5476a3000000");
        printf("Padding & appending #1 test passed!\n");

        bs_mv->append(zero);
        assert(data[3] == 0xff);
        assert(bs_mv->get_length() == 6);
        assert(bs_mv->hex_string() == "5476a3000000");
        printf("Padding & appending #2 test passed!\n");

        ByteStream *slice_a = bs_cp->slice(1, 2);
        assert(slice_a->hex_string() == "76a3");
        ByteStream *slice_b = bs_cp->slice(2, 3);
        assert(slice_b->hex_string() == "a30000");
        delete slice_a;
        delete slice_b;
        printf("Slicing test passed!\n");

        assert(*bs_cp == *bs_mv);
        assert(*bs_cp != *zero);
        printf("EQ & NEQ test passed!\n");

        delete bs_cp;
        delete bs_mv;
        delete zero;
#endif
    }
};