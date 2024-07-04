#ifndef COLOR_H
#define COLOR_H

#include "pixel.h"

#include <iostream>

color prepareVectorToWrite(const color& pixel_color,const float& scale);

pixelData preparePixelToWrite(const pixelData& data,const float& scale);

#endif