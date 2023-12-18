#ifndef CONVERTION_H
#define CONVERTION_H

#include "Bitmap.h"
#include "YUVFrame.h"
#include <stdint.h>

YUVFrame BMPToYUV(const Bitmap& bmp);

#endif