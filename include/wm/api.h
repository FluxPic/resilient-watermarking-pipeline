#pragma once
#include "types.h"
#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif

WM_Error wm_init();

WM_Error wm_embed(
    const WM_ImageBuffer* input,
    const WM_Payload* payload,
    const WM_Key* key,
    const WM_EmbedOptions* options,
    WM_ImageBuffer* output
);

WM_Error wm_extract(
    const WM_ImageBuffer* input,
    const WM_Key* key,
    WM_ExtractResult* result
);

void wm_shutdown();

#ifdef __cplusplus
}
#endif
/* api.h - C-compatible public API (placeholder) */