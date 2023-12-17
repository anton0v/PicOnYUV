#include "Convertion.h"

YUVFrame BMPToYUV(const Bitmap &bmp)
{
    unsigned int width = bmp.getWidth();
    unsigned int height = bmp.getHeight();

    if(width % 2 == 1) width--;
    if(height % 2 == 1) height--;

    unsigned int ySize = width * height;
    unsigned int cSize = ySize / 4;

    unsigned char *buffer = new unsigned char[ySize + 2*cSize];

    const unsigned char *rgb = bmp.getBuffer();

    int rPos = 0;
    int gPos = 3;
    int bPos = 6;

    int yPos = 0;
    int uPos = ySize;
    int vPos = ySize + cSize;

    for(int y = 0; y < height; ++y)
    {
        if(y % 2 == 0)
        {
            for(int x = 0; x < width; x += 2)
            {
                buffer[yPos++] = ((66 * rgb[rPos] + 129 * rgb[gPos] +  25 * rgb[bPos] + 128) >> 8) + 16;
                buffer[uPos++] = (( -38 * rgb[rPos] - 74 * rgb[gPos] + 112 * rgb[bPos] + 128) >> 8) + 128;
                buffer[vPos++] = (( 112 * rgb[rPos] - 94 * rgb[gPos] - 18 * rgb[bPos] + 128) >> 8) + 128;

                rPos += 3;
                gPos += 3;
                bPos += 3;

                buffer[yPos++] = ((66 * rgb[rPos] + 129 * rgb[gPos] + 25 * rgb[bPos] + 128) >> 8) + 16;

                rPos += 3;
                gPos += 3;
                bPos += 3;
            }
        }
        else
        {
            for(int x = 0; x < width; ++x)
            {
                buffer[yPos++] = ((66 * rgb[rPos] + 129 * rgb[gPos] + 25 * rgb[bPos] + 128) >> 8) + 16;

                rPos += 3;
                gPos += 3;
                bPos += 3;
            }
        }

        
    }

    return YUVFrame(width, height, buffer);
}