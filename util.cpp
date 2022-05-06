#include "SpongeFunction.hpp"
#include "ByteStream.hpp"

class NaiveSponge : public SpongeFunction {
private:
    virtual void F(ByteStream *) override { }
} hash;

std::string file_hash(std::string file_path) {
    // TODO
    return hash.forward(ByteStream::copy_from((uint8_t *) "Hello world", 12));
}

std::string string_hash(std::string input) {
    // TODO
    return hash.forward(ByteStream::copy_from(
        (uint8_t *) input.c_str(), input.length()
    ));
}
