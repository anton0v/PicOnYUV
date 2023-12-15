#include "YUVFrame.h"
#include <iostream>

YUVFrame::YUVFrame(int width, int height, const std::string path) :
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

YUVFrame::YUVFrame(int width, int height, unsigned char Y, 
                                          unsigned char Cb, 
                                          unsigned char Cr) :
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
    
    Fill(Y, Cb, Cr);
}

YUVFrame::~YUVFrame()
{
    if(_buffer != nullptr)
        delete _buffer;
}

bool YUVFrame::Fill(unsigned char Y, unsigned char Cb, unsigned char Cr)
{
    if(_buffer == nullptr)
        return false;
    
    std::fill(_buffer, &_buffer[_ySize], Y);
    std::fill(&_buffer[_ySize],
              &_buffer[_ySize + _cSize], Cb);
    std::fill(&_buffer[_ySize + _cSize],
              &_buffer[_bufferSize], Cr);

    return true;
}

bool YUVFrame::ReadFile(const std::string path)
{
    std::ifstream file(path);

    if(!file.good())
        return false;

    file.read((char*)_buffer, _bufferSize);

    file.close();
    return true;
}

bool YUVFrame::ToFile(const std::string path) const
{
    std::ofstream file(path);

    if(!file.good())
        return false;

    file.write((char*)_buffer, _bufferSize);

    file.close();
    return true;
}

bool YUVFrame::ReadFile(std::ifstream &input)
{
    if(!input.good())
        return false;

    input.read((char*)_buffer, _bufferSize);

    return true;
}

bool YUVFrame::ToFile(std::ofstream &output) const
{
    if(!output.good())
        return false;

    output.write((char*)_buffer, _bufferSize);

    return true;
}
