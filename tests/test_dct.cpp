#include <cassert>
#include <cmath>
#include <cstdio>

#include "wm/transform/dct.h"

using namespace wm;

static bool nearly_equal(float a, float b, float eps = 1e-3f) {
    return std::fabs(a - b) < eps;
}

// ----------------------------
// Test 1: Round-trip accuracy
// ----------------------------
void test_round_trip() {
    float input[64];
    float coeff[64];
    float output[64];

    for (int i = 0; i < 64; ++i)
        input[i] = static_cast<float>(i % 16);

    dct8x8(input, coeff);
    idct8x8(coeff, output);

    for (int i = 0; i < 64; ++i)
        assert(nearly_equal(input[i], output[i]));

    printf("[PASS] DCT round-trip\n");
}

// ----------------------------
// Test 2: DC-only block
// ----------------------------
void test_dc_only() {
    float input[64] = {0};
    float coeff[64] = {0};
    float output[64] = {0};

    for (int i = 0; i < 64; ++i)
        input[i] = 10.0f;

    dct8x8(input, coeff);

    // Only DC should be non-zero
    for (int i = 1; i < 64; ++i)
        assert(std::fabs(coeff[i]) < 1e-3f);

    idct8x8(coeff, output);

    for (int i = 0; i < 64; ++i)
        assert(nearly_equal(output[i], 10.0f));

    printf("[PASS] DCT DC-only\n");
}

// ----------------------------
// Main
// ----------------------------
int main() {
    test_round_trip();
    test_dc_only();

    printf("All DCT tests passed.\n");
    return 0;
}
