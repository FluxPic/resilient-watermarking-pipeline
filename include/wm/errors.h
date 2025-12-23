#pragma once

typedef enum {
    WM_OK = 0,
    WM_ERR_INVALID_IMAGE = -1,
    WM_ERR_INVALID_PAYLOAD = -2,
    WM_ERR_UNSUPPORTED_FORMAT = -3,
    WM_ERR_INTERNAL = -4,
    WM_ERR_EXTRACTION_FAILED = -5
} WM_Error;
