#pragma once

#include "SpongeFunction.hpp"
#include "ByteStream.hpp"

class NaiveSponge : public SpongeFunction {
private:
    virtual void F(ByteStream *bs) override { }
};

enum SpongeType {
    Naive,
};

SpongeFunction *create_hash(SpongeType type) {
    switch (type) {
        case SpongeType::Naive:
            return new NaiveSponge();
        default:
            assert(false);
    }
}

std::string file_hash(std::string file_path, SpongeType type = SpongeType::Naive, int hash_len = HASH_OUT_LEN) {
    SpongeFunction *hash = create_hash(type);
    FILE *fp = std::fopen(file_path.c_str(), "rb");

    if (!fp) {
        printf("Failed in opening file. Aborted.\n");
        assert(false);
    }

    uint8_t *buf = new uint8_t[MAX_READ_IN_LEN];
    memset(buf, 0, MAX_READ_IN_LEN);
    while (true) {
        size_t n;
        size_t len = 0;

        do {
            n = fread(buf + len, 1, MAX_READ_IN_LEN, fp);
            len += n;
        } while (len < MAX_READ_IN_LEN && n != 0);

        assert(!ferror(fp));
        if (len == 0) {
            break;
        }
        hash->absorb(ByteStream::move_from_raw(buf, len));
    }
    fclose(fp);
    
    std::string res = hash->squeeze(hash_len);
    delete hash;
    delete[] buf;
    return res;
}

std::string string_hash(std::string input, SpongeType type = SpongeType::Naive, int hash_len = HASH_OUT_LEN) {
    SpongeFunction *hash = create_hash(type);
    hash->absorb(ByteStream::copy_from_raw((uint8_t *) input.c_str(), input.length()));
    std::string res = hash->squeeze(hash_len);
    delete hash;
    return res;
}
