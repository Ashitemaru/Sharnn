#pragma once

#include "SpongeFunction.hpp"
#include "ByteStream.hpp"

class NaiveSponge : public SpongeFunction {
private:
    virtual void F(ByteStream *) override { }
} hash;

std::string file_hash(std::string file_path) {
    std::ifstream handle(file_path, std::ios::binary);

    if (!handle) {
        printf("Failed in opening file. Aborted.\n");
        assert(false);
    }

    // TODO: Handle huge files
    uint8_t *buf = new uint8_t[MAX_READ_IN_LEN];
    uint8_t ch = 0;
    int length = 0;
    for (; length < MAX_READ_IN_LEN; ++length) {
        ch = handle.get();
        if ((char) ch == EOF) break;
        else buf[length] = ch;
    }

    ByteStream *bs = ByteStream::move_from(buf, length);
    std::string res = hash.forward(bs);
    
    handle.close();
    delete bs;
    delete[] buf;
    return res;
}

std::string string_hash(std::string input) {
    // TODO
    ByteStream *bs = ByteStream::copy_from((uint8_t *) input.c_str(), input.length());
    std::string res = hash.forward(bs);
    delete bs;
    return res;
}
