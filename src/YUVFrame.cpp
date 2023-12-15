#include "YUVFrame.h"
#include <iostream>
#include <fstream>

YUVFrame::YUVFrame(int width, int height, std::string path) :
    _width(width),
    _height(height),
    _buffer(nullptr)
{
    if(_width <= 0 && _height <= 0)
        return;

    _ySize = _width * _height;
    _cSize = _ySize / 4;
    _bufferSize = _ySize + 2 * _cSize;
    _buffer = new unsigned char[_bufferSize];

    ReadFile(path);
}

YUVFrame::~YUVFrame()
{
    if(_buffer != nullptr)
        delete _buffer;
}

bool YUVFrame::ReadFile(std::string path)
{
    std::ifstream file(path);

    if(!file.good())
        return false;

    file.read((char*)_buffer, _bufferSize);

    file.close();
    return true;
}

bool YUVFrame::ToFile(std::string path) const
{
    std::ofstream file(path);

    if(!file.good())
        return false;

    file.write((char*)_buffer, _bufferSize);

    file.close();
    return true;
}
