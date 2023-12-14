#ifndef BITMAP_H
#define BITMAP_H

#include <string>

#pragma pack(push, 1)
struct bmpHeader
{
    unsigned short signature;
    unsigned int size;
    unsigned short resvd1;
    unsigned short resvd2;
    unsigned int offset;
};

struct bmpDIB
{
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int rawDataSize;
    unsigned int hres;
    unsigned int vres;
    unsigned int palette;
    unsigned int impColors;
};
#pragma pack(pop)

class Bitmap
{

public:
    Bitmap(const std::string path);
    ~Bitmap();

    void ToFile(const std::string path);

private:
    bmpHeader _header;
    bmpDIB _DIB;
    unsigned char *_buffer;
    unsigned int _bufferSize;
    unsigned int _padding;
    unsigned int _bytesPerPixel;
    unsigned int _lineSize;

    void CheckBMP();
};

#endif //BITMAP_H