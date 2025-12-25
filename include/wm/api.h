#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WM_OK = 0,
    WM_ERR_INVALID_ARGUMENT,
    WM_ERR_INVALID_DIMENSIONS,
    WM_ERR_INSUFFICIENT_CAPACITY,
    WM_ERR_INTERNAL,
    WM_ERR_UNVERIFIABLE
} WM_Status;

typedef enum {
    WM_VERDICT_VERIFIED = 0,
    WM_VERDICT_TAMPERED,
    WM_VERDICT_UNVERIFIABLE
} WM_Verdict;

typedef struct {
    uint32_t width;
    uint32_t height;
    float* y;
} WM_Image;

typedef struct {
    const int8_t* bits;   // MUST be int8_t
    uint32_t length;
} WM_Payload;

typedef struct {
    int8_t* bits;
    float* confidence;
    uint32_t length;

    float mean_confidence;
    float min_confidence;

    WM_Verdict verdict;
} WM_ExtractResult;

WM_Status wm_embed(
    WM_Image* image,
    const WM_Payload* payload,
    uint64_t key,
    float alpha
);

WM_Status wm_extract(
    WM_Image* image,
    uint64_t key,
    WM_ExtractResult* result
);

#ifdef __cplusplus
}
#endif
