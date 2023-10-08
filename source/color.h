#ifndef COLOR_H
#define COLOR_H

#include "pixel.h"

#include <iostream>

color prepare_vector_to_write(const color& pixel_color,const float& scale);

pixel_data prepare_pixel_to_write(const pixel_data& data,const float& scale);

#endif