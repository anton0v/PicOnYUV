#include <iostream>
#include <fstream>
#include "Bitmap.h"
#include "YUVFrame.h"
#include "Convertion.h"

int main(int argc, char **argv)
{
    try
    {
        Bitmap bmp("res/angry.bmp");
        bmp.ToFile("res/aga.bmp");

        YUVFrame picture = BMPToYUV(bmp, true);
        YUVFrame picture2 = BMPToYUV(bmp, false);
        picture.ToFile("res/Opa.yuv");

        std::ifstream input("res/cat.yuv", std::ios::binary);
        std::ofstream output("res/out.yuv", std::ios::binary);
        YUVFrame frame(640, 360, 255, 125, 125);

        for(int i = 0; i < 221; ++i)
        {
            frame.ReadFile(input);
            frame.InjectFrame(50, 50, picture);
            frame.InjectFrame(200, 50, picture2);
            frame.ToFile(output);
        }

        input.close();
    }
    catch(const char* e)
    {
        std::cerr << e << '\n';
    }

    return EXIT_SUCCESS;
}