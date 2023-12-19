#include "Convertion.h"
#include <iostream>
#include <thread>

void BGR24LinesToYUV(unsigned int begin, unsigned int end, 
                     unsigned char *buffer, const unsigned char *rgb, 
                     unsigned int rgbWidth, unsigned int rgbHeight, bool flipped)
{
    unsigned int rowCount = end - begin;
    char sign = 1;

    //from odd width rgb to 2x2 yuv
    unsigned int oddWidthBytes = (rgbWidth % 2 != 0) * 3;
    unsigned int width = oddWidthBytes ? rgbWidth - 1: rgbWidth;
    unsigned int height = (rgbHeight % 2 != 0) ? rgbHeight - 1: rgbHeight;

    unsigned int ySize = width * height;
    unsigned int cSize = ySize / 4;

    unsigned int rPos , gPos, bPos;
    unsigned int yPos, uPos, vPos;
    unsigned int y;

    if (flipped)
    {
        sign = -1;
        y = (end - 1);
        rPos = 2 + y * rgbWidth * 3;
        gPos = 1 + y * rgbWidth * 3;
        bPos = y * rgbWidth * 3;

        yPos = (rgbHeight - end) * width;
        uPos = ySize + (rgbHeight - end) * width / 4;
        vPos = ySize + cSize + (rgbHeight - end) * width / 4;

        if(end % 2 != 0)
        {
            uPos -= width / 4;
            vPos -= width / 4;
        }
    }
    else
    {
        rPos = 2 + begin * rgbWidth * 3;
        gPos = 1 + begin * rgbWidth * 3;
        bPos = begin * rgbWidth * 3;
        y = begin;

        yPos = begin * width;
        uPos = ySize + begin * width / 4;
        vPos = ySize + cSize + begin * width / 4;

        if(begin % 2 != 0)
        {
            uPos += width / 4;
            vPos += width / 4;
        }
    }

    for(unsigned int i = 0; i < rowCount; ++i)
    {
        if(y % 2 == 0)
        {
            for(int x = 0; x < width; x += 2)
            {
                buffer[yPos++] = ((66 * rgb[rPos] + 129 * rgb[gPos] + 25 * rgb[bPos] + 128) >> 8) + 16;
                buffer[uPos++] = ((-38 * rgb[rPos] -74 * rgb[gPos] + 112 * rgb[bPos] + 128) >> 8) + 128;
                buffer[vPos++] = ((112 * rgb[rPos] -94 * rgb[gPos] -18 * rgb[bPos] + 128) >> 8) + 128;

                rPos += 3; gPos += 3; bPos += 3;

                buffer[yPos++] = ((66 * rgb[rPos] + 129 * rgb[gPos] + 25 * rgb[bPos] + 128) >> 8) + 16;

                rPos += 3; gPos += 3; bPos += 3;
            }
        }
        else
        {
            for(int x = 0; x < width; ++x)
            {
                buffer[yPos++] = ((66 * rgb[rPos] + 129 * rgb[gPos] + 25 * rgb[bPos] + 128) >> 8) + 16;

                rPos += 3; gPos += 3; bPos += 3;
            }
        }
        y += sign;
        rPos = 2 + (y) * rgbWidth * 3; gPos = rPos - 1; bPos = rPos - 2;
        
    }
}

YUVFrame BMPToYUV(const Bitmap &bmp, bool flipped)
{
    unsigned int oldWidth = bmp.getWidth();
    unsigned int height = bmp.getHeight();
    unsigned int width = oldWidth;
    unsigned int wSpace = 0;

    if(width % 2 == 1) 
    {
        width--;
        wSpace = 3;
    }
    if(height % 2 == 1) height--;

    unsigned int ySize = width * height;
    unsigned int cSize = ySize / 4;

    unsigned char *buffer = new unsigned char[ySize + 2*cSize];

    const unsigned char *rgb = bmp.getBuffer();

    int threadCount = std::thread::hardware_concurrency();
    std::thread threads[threadCount];

    unsigned int rowCount = height / threadCount;
    unsigned int freeRows = height % threadCount;
    int active = 0;
    unsigned int begin = 0, end = 0;
    for(active; active < threadCount - 1; ++active)
    {
        end = (freeRows && active < freeRows) ? begin + rowCount + 1 
									  : begin + rowCount;
        
        threads[active] = std::thread(BGR24LinesToYUV, begin, end,
                                      buffer, rgb, oldWidth, height, flipped);

        begin = end;
    }

    BGR24LinesToYUV(begin, height, buffer, rgb, oldWidth, height, flipped);

    for (int i = 0; i < active; i++)
	{
		threads[i].join();
	}

    return YUVFrame(width, height, buffer);
}