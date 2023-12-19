#ifndef CONVERTION_H
#define CONVERTION_H

#include "Bitmap.h"
#include "YUVFrame.h"

YUVFrame BMPToYUV(const Bitmap& bmp, bool flipped);

#endif