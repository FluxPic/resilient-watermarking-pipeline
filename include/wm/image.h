#pragma once
#include "types.h"
#include "api.h"

namespace wm {

struct Image {
    uint32_t width;
    uint32_t height;
    float* Y;   // luminance channel
};

WM_Status validate_image(const WM_ImageBuffer* img);
Image to_luminance(const WM_ImageBuffer* img);
void free_image(Image& img);

} // namespace wm
