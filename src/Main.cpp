#include <iostream>
#include <fstream>
#include "Bitmap.h"
#include "YUVFrame.h"

int main(int argc, char **argv)
{
    std::ifstream in("res/cat.yuv", std::ios_base::binary);
    std::ofstream out("res/output.yuv", std::ios_base::binary);

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

    return EXIT_SUCCESS;
}