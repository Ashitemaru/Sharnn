#include <cstdint>
#include <iostream>
#include <random>
#include <streambuf>

#include "RNNHash.hpp"

const int data_size = 300;
uint8_t ori_data[data_size], data[data_size];

char str_data[] =
    "2c98586dea0397ab5951d653f0c86a20a9b8f4c657f3fb2646d5aaa0e6db2abb669c01f2ee"
    "54d9753b1c6fa4f1ec4be7d6f693a87a71d4419ede68a65750afd15a9220be835e749d79f4"
    "9bee49d68b136b9b88bd53ed27a4ecf67ef4a382bfc37b3accd9ec4a9b0e9205e04d1d0523"
    "9cd93e2075a444a2cdc95165b7ff2cbe24eff636672c167d387715f04c976dd12ec1c4ca7d"
    "ecd5f3a359740cdec34b50908579a18a1c61718271d4fb460eb9ad74b59450f441a78af11c"
    "7598a7aeba096fae4291e5c2c9eb1983ff448cfff6564dd3ba86a9d8929e04258953601e73"
    "8ad9540a372d720efbf95871289d9a9c3161776423e5c410e0c6eda2f5a29786168b2f1907"
    "72c36c4649ac71bb1b1d27347eb50eab54991d119704176dd7e4ec3e46ac1c39037609b90c"
    "8a4f7712fa63e3280b9c0f09cfde2f24fab16c23c227d112368f9ff214f9480d6342b3a7c8"
    "aee16ad1eff4a4b185b5ecd3ede88d8d8311f168cbcfc3a137a15e4459a9053aaf373b9fc4"
    "9580d65ebfaaa4d22ee9f33900ff67061693307a61770d551feb487b9fe2b7ab1954e812ee"
    "fb0b1b67e95e641f38845eaf3777958c37d5b60cecf7277997520ede527ab65066c0367d72"
    "2545cd4bd0f7407c02bca11b3ac22f9547f9614aa62ca41de13bec487aee22ed3ecac634f6"
    "5ddbb19feb87c9fd6abafcd8bb4fee5b41f51e0c597ca21646a14def0776a71529d8969acb"
    "8ab84a33a69d96b2673eddb693c9c3f93a2d77367f5d44c444acea08bf76b0ed63bee2be7a"
    "9340acce84e64cc9c58678b06858647947b7bf3dcd68832698e805c266ce82f83ad34bf434"
    "1c3797f9c338ce7d8b99daa0b7b037f595b98adc096e6744497bc07db01aaa4b521d96cb5e"
    "667dc78289054ba00fbbb0f141e234ef39efe9460305ce8ee5154e06c5ea40d3e0ab392218"
    "90b322d19cf9d1e25078812e7cf38cf26985d5d20e02ab3ec33a573c80b2726c944749a10e"
    "de1fd2372cb1b342666413f72911cafde750b99bead2778ee16e43a769db6217e473f50bd2"
    "10761808533a6fcba8ad5e4e519b956037cac864d7f0cd6c82a587556c5c5b3a152f995dcc"
    "7403446fcdb918923876e5212a03608c938ecfbe4cf52b670eb377b3c55e729082a8b37f98"
    "25449f69fc03733b57a82545607812f886ccea7c1bd960864760cea61fe8de467427fa9db5"
    "2ee94cc281566690f340dfb15e33b8af082e5923ba7dcb7f59fda856be3bc5a6691154d56e"
    "1f99250a04ce4f00064b721bb01f92a3b5eee262122045240c447b3fc0e7971abc82f79d24"
    "f35edb1ed5014c82d88a95641a296e9bd80cf57101b5eb85f22e533b5840bdbdc44e7b4cd0"
    "48e26caadd1b036069a5c5be0f457f6f6209dd1cd68534af80dfd41d982606aeda18e04090"
    "62c0f30ddf7b1542642101add469052c37c3e288912bf9bab8";

char str_data_2[] =
    "2c98586dea0397ab5951d653f0c86a20a9b8f4c657f3fb2646d5aaa0e6db2abb669c01f2ee"
    "54d975bb1c6fa4f1ec4be7d6f693a87a71d4419ede68a65750afd15a9220be835e749d79f4"
    "9bee49d68b136b9b88bd53ed27a4ecf67ef4a382bfc37b3accd9ec4a9b0e9205e04d1d0523"
    "9cd93e2075a444a2cdc95165b7ff2cbe24eff636672c167d387715f04c976dd12ec1c4ca7d"
    "ecd5f3a359740cdec34b50908579a18a1c61718271d4fb460eb9ad74b59450f441a78af11c"
    "7598a7aeba096fae4291e5c2c9eb1983ff448cfff6564dd3ba86a9d8929e04258953601e73"
    "8ad9540a372d720efbf95871289d9a9c3161776423e5c410e0c6eda2f5a29786168b2f1907"
    "72c36c4649ac71bb1b1d27347eb50eab54991d119704176dd7e4ec3e46ac1c39037609b90c"
    "8a4f7712";

struct membuf : std::streambuf {
    membuf(char *begin, uint32_t size) {
        this->setg(begin, begin, begin + size);
    }
};

uint32_t random_number(uint32_t rand_max) {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist(
        0, 0xFFFFFFFF);
    return dist(rng) % rand_max;
}

void print_data(uint8_t *data) {
    for (int i = 0; i < data_size; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(2)
                  << (uint32_t) data[i];
    }
    std::cout << std::endl;
}

int main() {
    //    for (uint8_t &i : ori_data) {
    //        i = random_number(256);
    //    }
    for (int i = 0; i < data_size; i++) {
        uint8_t a1 = str_data[i << 1] >= 'a' ? 10 + str_data[i << 1] - 'a'
                                             : str_data[i << 1] - '0';
        uint8_t a2 = str_data[i << 1 | 1] >= 'a'
                         ? 10 + str_data[i << 1 | 1] - 'a'
                         : str_data[i << 1 | 1] - '0';
        ori_data[i] = (a1 << 4) + a2;
    }

    for (int i = 0; i < data_size; i++) {
        uint8_t a1 = str_data_2[i << 1] >= 'a' ? 10 + str_data_2[i << 1] - 'a'
                                               : str_data_2[i << 1] - '0';
        uint8_t a2 = str_data_2[i << 1 | 1] >= 'a'
                         ? 10 + str_data_2[i << 1 | 1] - 'a'
                         : str_data_2[i << 1 | 1] - '0';
        data[i] = (a1 << 4) + a2;
    }

    print_data(ori_data);
    RNNHash::Out_t out1, out2;
    RNNHash h;

    {
        membuf buf{reinterpret_cast<char *>(ori_data), data_size};
        std::istream input(&buf);
        out1 = h(input);
        std::cout << "Hash: " << out1.to_hex_string() << std::endl;
    }

    //    {
    //        RNNHash h;
    //        membuf buf{reinterpret_cast<char *>(data), data_size};
    //        std::istream input(&buf);
    //        out2 = h(input);
    //        std::cout << "Hash: " << out2.to_hex_string() << std::endl;
    //    }

    for (int i = 0; i < 100000; i++) {
        uint32_t pos = random_number(data_size);
        uint32_t bit = random_number(8);
        std::copy_n(ori_data, data_size, data);
        data[pos] ^= 1 << bit;

        membuf buf{reinterpret_cast<char *>(data), data_size};
        std::istream input(&buf);
        out2 = h(input);
        if (out1 == out2) {
            std::cout << std::dec << pos << " " << bit << " : ";
            print_data(data);
            return -1;
        }
    }

    printf("TEST PASS");
}