#include <iostream>
#include "Bitmap.h"
#include "YUVFrame.h"

int main(int argc, char **argv)
{
    try
    {
        Bitmap bmp("res/1.bmp");
        bmp.ToFile("res/hihi.bmp");

        YUVFrame frame(640, 360);
        frame.ReadFile("res/cat.yuv");
        frame.ToFile("res/firstFrame.yuv");
    }
    catch(const char* e)
    {
        std::cerr << e << '\n';
    }

    return EXIT_SUCCESS;
}