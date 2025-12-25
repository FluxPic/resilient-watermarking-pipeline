#include "wm/image.h"
#include <cstdlib>

namespace wm {

WM_Status validate_image(const WM_ImageBuffer* img) {
    if (!img || !img->data)
        return WM_ERR_INVALID_ARGUMENT;
    if (img->channels != 3)
        return WM_ERR_INVALID_ARGUMENT;
    if (img->width == 0 || img->height == 0)
        return WM_ERR_INVALID_ARGUMENT;
    return WM_OK;
}

Image to_luminance(const WM_ImageBuffer* img) {
    Image out;
    out.width = img->width;
    out.height = img->height;
    out.Y = (float*)std::malloc(sizeof(float) * out.width * out.height);

    const uint8_t* rgb = img->data;

    for (uint32_t i = 0; i < out.width * out.height; ++i) {
        float r = rgb[3 * i + 0];
        float g = rgb[3 * i + 1];
        float b = rgb[3 * i + 2];

        // ITU-R BT.601 luminance
        out.Y[i] = 0.299f * r + 0.587f * g + 0.114f * b;
    }
    return out;
}

void free_image(Image& img) {
    if (img.Y) {
        std::free(img.Y);
        img.Y = nullptr;
    }
}

} // namespace wm
