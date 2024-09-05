#include "imageSave.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

void saveToPng(const SaveParams& params,const std::vector<uint8_t>& image_data) {
    const std::string file_name = params.file_name + ".png";
    const uint32_t channels = static_cast<uint32_t>(params.format);

    stbi_write_png(file_name.c_str(),params.width,params.height,channels,image_data.data(),channels * params.width);
}

void saveToJpg(const SaveParams& params,const std::vector<uint8_t>& image_data,const uint32_t& quality) {
    const std::string file_name = params.file_name + ".jpg";
    const uint32_t channels = static_cast<uint32_t>(params.format);

    stbi_write_jpg(file_name.c_str(),params.width,params.height,channels,image_data.data(),quality);
}

void saveToTga(const SaveParams& params,const std::vector<uint8_t>& image_data) {
    const std::string file_name = params.file_name + ".tga";
    const uint32_t channels = static_cast<uint32_t>(params.format);

    stbi_write_tga(file_name.c_str(),params.width,params.height,channels,image_data.data());
}