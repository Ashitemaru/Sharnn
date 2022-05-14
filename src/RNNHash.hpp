#include "ChaoticMap.hpp"
#include "ChaoticSystem.hpp"
#include "RNN.hpp"
#include "SpongeHash.hpp"

class RNNHash : public SpongeHash<136, 64, 32> {};