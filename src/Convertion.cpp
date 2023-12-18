#include "Convertion.h"
#include <iostream>
#include <thread>

void BGR24LinesToYUV(unsigned int begin, unsigned int end, 
                     unsigned char *buffer, const unsigned char *rgb, 
                     unsigned int rgbWidth, unsigned int rgbHeight)
{
    unsigned int oddWidthBytes = (rgbWidth % 2 != 0) * 3;
    unsigned int width = oddWidthBytes ? rgbWidth - 1: rgbWidth;
    unsigned int height = (rgbHeight % 2 != 0) ? rgbHeight - 1: rgbHeight;

    unsigned int ySize = width * height;
    unsigned int cSize = ySize / 4;

    unsigned int rPos = 2 + begin * rgbWidth * 3;
    unsigned int gPos = 1 + begin * rgbWidth * 3;
    unsigned int bPos = begin * rgbWidth * 3;

    unsigned int yPos = begin * width;
    unsigned int uPos = ySize + begin * width / 4;
    unsigned int vPos = ySize + cSize + begin * width / 4;

    if(begin % 2 != 0)
    {
        uPos += width / 4;
        vPos += width / 4;
    }

    for(unsigned int y = begin; y < end; ++y)
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
        rPos += oddWidthBytes; gPos += oddWidthBytes; bPos += oddWidthBytes;
        
    }
}

YUVFrame BMPToYUV(const Bitmap &bmp)
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
                                      buffer, rgb, oldWidth, height);

        begin = end;
    }

    BGR24LinesToYUV(begin, height, buffer, rgb, oldWidth, height);

    for (int i = 0; i < active; i++)
	{
		threads[i].join();
	}

    return YUVFrame(width, height, buffer);
}