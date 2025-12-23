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
typedef struct {
    uint8_t bits[64];     // each bit is 0 or 1
} WM_Payload;

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

// --------------------
// Extraction result
// --------------------
typedef struct {
    uint8_t bits[64];
    float confidence;         // 0.0 – 1.0
    uint8_t success;          // 1 = success, 0 = fail
} WM_ExtractResult;

#ifdef __cplusplus
}
#endif
