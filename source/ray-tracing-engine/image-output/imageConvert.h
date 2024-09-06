#ifndef IMAGE_CONVERT
#define IMAGE_CONVERT

#include "../renderLayer.h"

std::vector<uint8_t> convertToBW(const RenderLayer& render_lay);

std::vector<uint8_t> convertToRGB(const RenderLayer& render_lay);

std::vector<uint8_t> convertToRGBA(const RenderLayer& render_lay);
#endif