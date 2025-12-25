#include <cassert>
#include <cstdio>
#include <vector>

#include "wm/api.h"

int main() {
    constexpr uint32_t W = 512;
    constexpr uint32_t H = 512;
    constexpr uint32_t PAYLOAD_LEN = 64;
    constexpr uint64_t KEY = 0xABCDEF1234567890ULL;

    // ----------------------------
    // Prepare luminance image
    // ----------------------------
    std::vector<float> Y(W * H, 128.0f);

    WM_Image img;
    img.width = W;
    img.height = H;
    img.y = Y.data();

    // ----------------------------
    // Prepare payload
    // ----------------------------
    int8_t payload_bits[PAYLOAD_LEN];
    for (uint32_t i = 0; i < PAYLOAD_LEN; ++i)
        payload_bits[i] = (i & 1) ? +1 : -1;

    WM_Payload payload;
    payload.bits = payload_bits;
    payload.length = PAYLOAD_LEN;

    // ----------------------------
    // Embed
    // ----------------------------
    WM_Status st = wm_embed(&img, &payload, KEY, 2.0f);
    assert(st == WM_OK);

    // ----------------------------
    // Prepare extraction buffers
    // ----------------------------
    std::vector<int8_t> out_bits(PAYLOAD_LEN);
    std::vector<float> confidence(PAYLOAD_LEN);

    WM_ExtractResult result;
    result.bits = out_bits.data();
    result.confidence = confidence.data();
    result.length = PAYLOAD_LEN;

    // ----------------------------
    // Extract
    // ----------------------------
    st = wm_extract(&img, KEY, &result);
    assert(st == WM_OK);

    // ----------------------------
    // Validate
    // ----------------------------
    printf("Verdict          : %d\n", result.verdict);
    printf("Mean confidence  : %.3f\n", result.mean_confidence);
    printf("Min confidence   : %.3f\n", result.min_confidence);

    assert(result.verdict == WM_VERDICT_VERIFIED);
    assert(result.mean_confidence > 0.9f);

    printf("ABI TEST PASSED\n");
    return 0;
}
