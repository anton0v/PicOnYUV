#ifndef YUVFRAME_H
#define YUVFRAME_H

#include <string>

class YUVFrame
{
public:
    YUVFrame(int width, int height, std::string path = "");
    ~YUVFrame();

    bool ReadFile(std::string path);
    bool ToFile(std::string path) const;

private:
    unsigned char *_buffer;
    unsigned int _width;
    unsigned int _height;
    unsigned int _ySize; //Y
    unsigned int _cSize; //CbCr
    unsigned int _bufferSize;
};


#endif