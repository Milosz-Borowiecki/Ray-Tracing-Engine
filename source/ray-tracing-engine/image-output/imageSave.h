#ifndef IMAGE_SAVER
#define IMAGE_SAVER
#include <algorithm>
#include <string>
#include <vector>

enum class ColorFormats {
    BW = 1,
    RGB = 3,
    RGBA = 4 
};

struct SaveParams {
    std::string file_name;
    uint32_t width;
    uint32_t height;
    ColorFormats format;
};

void saveToPng(const SaveParams& params,const std::vector<uint8_t>& image_data);

void saveToJpg(const SaveParams& params,const std::vector<uint8_t>& image_data,const uint32_t& quality);

void saveToTga(const SaveParams& params,const std::vector<uint8_t>& image_data);
#endif