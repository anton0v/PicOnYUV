#include <iostream>
#include <fstream>
#include "Bitmap.h"
#include "YUVFrame.h"

int main(int argc, char **argv)
{
    try
    {
        Bitmap bmp("res/1.bmp");
        bmp.ToFile("res/hihi.bmp");

        std::ifstream in("res/cat.yuv");
        std::ofstream out("res/output.yuv");

        YUVFrame frame(640, 360, rand() % 256, 
                                 rand() % 256, 
                                 rand() % 256);

        frame.ToFile("res/what.yuv");

        for(int i = 0; i < 10; ++i)
        {
            frame.ToFile(out);
            if(i % 2 != 0)
                frame.Fill(rand() % 256, rand() % 256, rand() % 256);
            else
                frame.ReadFile(in); // "in" is not good
        }

        out.close();
        in.close();

    }
    catch(const char* e)
    {
        std::cerr << e << '\n';
    }

    return EXIT_SUCCESS;
}