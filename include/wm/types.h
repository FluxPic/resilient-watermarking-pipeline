#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// --------------------
// Image representation
// --------------------
typedef struct {
    uint32_t width;
    uint32_t height;
    uint8_t channels;     // must be 3 (RGB)
    uint8_t* data;        // size = width * height * channels
} WM_ImageBuffer;

// --------------------
// Watermark payload
// --------------------

// --------------------
// Watermark key
// --------------------
typedef struct {
    uint64_t seed;
} WM_Key;

// --------------------
// Embedding options
// --------------------
typedef struct {
    float strength_scale;     // default = 1.0
    uint32_t redundancy;      // blocks per bit (default ~48)
} WM_EmbedOptions;



#ifdef __cplusplus
}
#endif
