#ifndef YUVFRAME_H
#define YUVFRAME_H

#include <string>
#include <fstream>

class YUVFrame
{
public:
    YUVFrame(int width, int height, const std::string path = "");
    YUVFrame(int width, int height, unsigned char Y,
                                    unsigned char Cb,
                                    unsigned char Cr);
    ~YUVFrame();

    bool Fill(unsigned char Y, unsigned char Cb, unsigned char Cr);

    bool ReadFile(const std::string path);
    bool ToFile(const std::string path) const;

    bool ReadFile(std::ifstream &input);
    bool ToFile(std::ofstream &output) const;

    unsigned int getWidth() const {return _width;}
    unsigned int getHeight() const {return _width;}
    unsigned int getByteSize() const {return _bufferSize;}

private:
    unsigned char *_buffer;
    unsigned int _width;
    unsigned int _height;
    unsigned int _ySize; //Y
    unsigned int _cSize; //CbCr
    unsigned int _bufferSize;
};


#endif