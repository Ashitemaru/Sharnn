#include <cstdio>
#include <cstdint>
#include <functional>
#include <string>
#include "SpongeFunction.h"


void F(uint8_t* state, uint64_t length) {}

int main() {

    // Reading Parameters...
    printf("Hello world!\n");


    SpongeFunction sponge((std::function<void(uint8_t*, uint64_t)>(F)));
    std::string raw_input = "Hello world!";
    sponge.Absorb((uint8_t*)raw_input.c_str(), raw_input.length());
    auto hash = sponge.Squeeze();
    printf("%s\n", hash.c_str());


    return 0;
}