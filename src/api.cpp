#include "wm/api.h"

#include "wm/image.h"
#include "wm/watermark/embed_image.h"
#include "wm/watermark/extract_image.h"

#include <cmath>

extern "C" {

// ----------------------------
// Internal verdict helper
// ----------------------------
static WM_Verdict compute_verdict(
    float mean_conf,
    float min_conf,
    uint32_t weak_bits,
    uint32_t total_bits
) {
    if (mean_conf >= 0.7f &&
        min_conf  >= 0.3f &&
        weak_bits <= total_bits * 0.1f)
        return WM_VERDICT_VERIFIED;

    if (mean_conf < 0.6f ||
        weak_bits >= total_bits * 0.25f)
        return WM_VERDICT_TAMPERED;

    return WM_VERDICT_UNVERIFIABLE;
}

// ----------------------------
// wm_embed
// ----------------------------
WM_Status wm_embed(
    WM_Image* image,
    const WM_Payload* payload,
    uint64_t key,
    float alpha
) {
    if (!image || !payload || !payload->bits)
        return WM_ERR_INVALID_ARGUMENT;

    if (!image->y || payload->length == 0)
        return WM_ERR_INVALID_ARGUMENT;

    wm::Image img;
    img.width  = image->width;
    img.height = image->height;
    img.Y      = image->y;

    bool ok = wm::embed_image(
        img,
        payload->bits,
        payload->length,
        key,
        alpha
    );

    return ok ? WM_OK : WM_ERR_INVALID_DIMENSIONS;
}

// ----------------------------
// wm_extract
// ----------------------------
WM_Status wm_extract(
    WM_Image* image,
    uint64_t key,
    WM_ExtractResult* result
) {
    if (!image || !result || !result->bits || !result->confidence)
        return WM_ERR_INVALID_ARGUMENT;

    if (!image->y || result->length == 0)
        return WM_ERR_INVALID_ARGUMENT;

    wm::Image img;
    img.width  = image->width;
    img.height = image->height;
    img.Y      = image->y;

    bool ok = wm::extract_image(
        img,
        result->bits,
        result->confidence,
        result->length,
        key
    );

    if (!ok)
        return WM_ERR_UNVERIFIABLE;

    // ----------------------------
    // Aggregate confidence
    // ----------------------------
    float sum = 0.0f;
    float min_conf = 1.0f;
    uint32_t weak = 0;

    for (uint32_t i = 0; i < result->length; ++i) {
        float c = result->confidence[i];
        sum += c;
        if (c < min_conf) min_conf = c;
        if (c < 0.6f) weak++;
    }

    result->mean_confidence = sum / result->length;
    result->min_confidence  = min_conf;
    result->verdict = compute_verdict(
        result->mean_confidence,
        result->min_confidence,
        weak,
        result->length
    );

    return WM_OK;
}

} // extern "C"
