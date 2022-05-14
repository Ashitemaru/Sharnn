
// Discrete Skew Tent map
template <int N> class DSTmap {
  const int twoN = 1 << N;

public:
  int operator()(int ks, int q) {
    assert(1 < q && q < twoN);
    assert(1 < ks && ks < twoN);

    long long x = ks;
    if (x < q) {
      return (x << N) / q;
    } else if (x == q) {
      return twoN - 1;
    } else if (x < twoN) {
      return ((twoN - ks) << N) / (twoN - q);
    }
  }
};

// Discrete Piecewise Linear Chaotic map
template <int N> class DPWLCmap {
  const int twoN = 1 << N;
  const int twoN_1 = 1 << (N - 1);

public:
  int operator()(int ks, int q) {
    assert(1 < q && q < twoN_1);
    assert(1 < ks && ks < twoN);

    long long x = ks;
    if (x <= q) {
      return (x << N) / q;
    } else if (x <= twoN_1) {
      return ((x - q) << N) / (twoN_1 - q);
    } else if (x <= twoN - q) {
      return ((twoN - x - q) << N) / (twoN_1 - q);
    } else if (x <= twoN - 1) {
      return ((twoN - x) << N) / q;
    } else {
      return twoN - 1 - q;
    }
  }
};