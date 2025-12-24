#pragma once
#include <cstdint>

namespace wm {

// In-place 8×8 DCT
void dct8x8(const float* input, float* output);

// In-place 8×8 inverse DCT
void idct8x8(const float* input, float* output);

} // namespace wm
