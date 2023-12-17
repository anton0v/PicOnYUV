#include "Bitmap.h"

#include <iostream>
#include <fstream>

Bitmap::Bitmap(const std::string path) :
    _padding(0)
{
    std::ifstream file(path, std::ios_base::binary);

    if(!file.good())
    {
        throw "Can't open a file";
    }

    file.read((char*)&(_header), sizeof(_header));
    file.read((char*)&(_DIB), sizeof(_DIB));

    CheckBMP();

    _width = _DIB.width;
    _height = _DIB.height;

    file.seekg(_header.offset, file.beg);

    _bytesPerPixel = _DIB.bpp / 8;
    _bufferSize = _width * _height * _bytesPerPixel;
    _buffer = new unsigned char[_bufferSize];
   
    //padding multiple of 4
    if(_width % 4 != 0)
    {
        _lineSize = _width * _bytesPerPixel;
        _padding = 4 - (_lineSize % 4);
        char *padBytes = new char[_padding] {0};
        for(int y = 0; y < _height; y++)
        {
            file.read((char*)_buffer + y * _lineSize, _lineSize);
            file.read(padBytes, _padding);
        }
        delete[] padBytes;
    }
    else
        file.read((char*)_buffer, _bufferSize);

    file.close();
}

Bitmap::~Bitmap()
{
    delete[] _buffer;
}

void Bitmap::ToFile(const std::string path)
{
    CheckBMP();

    std::ofstream file(path, std::ios_base::binary);

    if(!file.good())
    {
        throw "Can't write to file";
    }

    file.write((char*)&(_header), sizeof(_header));
    file.write((char*)&(_DIB), sizeof(_DIB));

    if(_padding)
    {
        char *padBytes = new char[_padding] {0};
        for(int y = 0; y < _DIB.height; y++)
        {
            file.write((char*)_buffer + y * _lineSize, _lineSize);
            file.write(padBytes, _padding);
        }
        delete[] padBytes;
    }
    else
        file.write((char*)_buffer, _bufferSize);

}

void Bitmap::CheckBMP()
{
    if(_header.signature != 0x4D42)
    {
        throw "Not a bmp file";
    }

    if(_DIB.bpp != 24)
    {
        throw "Supports 24 bit per pixel only";
    }

    if(_DIB.compression != 0)
    {
        throw "Do not supports compression";
    }

    if(_DIB.palette != 0)
    {
        throw "Do not supports palette";
    }
}
