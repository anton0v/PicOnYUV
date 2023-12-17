#include "YUVFrame.h"
#include <iostream>

YUVFrame::YUVFrame(int width, int height, const std::string path) :
    _width(width),
    _height(height),
    _colorWidth(width/2),
    _colorHeight(height/2),
    _buffer(nullptr)
{
    if(_width <= 0 || _height <= 0)
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
    _colorWidth(width/2),
    _colorHeight(height/2),
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

bool YUVFrame::InjectFrame(int x, int y, const YUVFrame &other)
{
    if(x < 0 || y < 0 || x > _width || y > _height)
        return false;
    
    unsigned int rowSize = x + other._width > _width
                            ? _width - x : other._width;
    
    unsigned int rowCount = y + other._height > _height
                            ? _height - y : other._height;

    unsigned int cRowSize = rowSize / 2;
    
    int otherYPos = 0;
    int otherUPos = other._ySize;
    int otherVPos = other._ySize + other._cSize;

    int yPos = x + y * _width;
    int uPos = x/2 + y/2 * _colorWidth + _ySize;
    int vPos = x/2 + y/2 * _colorWidth + _ySize + _cSize;

    char isEvenRow = y % 2;

    for(int i = 0; i < rowCount; ++i)
    {
        std::copy(&other._buffer[otherYPos], 
                  &other._buffer[otherYPos + rowSize],
                  &_buffer[yPos]);

        otherYPos += other._width;
        yPos += _width;

        if(i % 2 == 0)
        {
            std::copy(&other._buffer[otherUPos], 
                  &other._buffer[otherUPos + cRowSize],
                  &_buffer[uPos]);

            otherUPos += other._colorWidth;
            uPos += _colorWidth;

            std::copy(&other._buffer[otherVPos], 
                  &other._buffer[otherVPos + cRowSize],
                  &_buffer[vPos]);

            otherVPos += other._colorWidth;
            vPos += _colorWidth;
        }
    }

    return true;
}

bool YUVFrame::ReadFile(const std::string path)
{
    std::ifstream file(path, std::ios_base::binary);

    if(!file.good())
        return false;

    file.read((char*)_buffer, _bufferSize);

    file.close();
    return true;
}

bool YUVFrame::ToFile(const std::string path) const
{
    std::ofstream file(path, std::ios_base::binary);

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
