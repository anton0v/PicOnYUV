#include <iostream>
#include <fstream>
#include "Bitmap.h"
#include "YUVFrame.h"

int main(int argc, char **argv)
{

    YUVFrame board(640, 360, 0, 125, 125);
    
    YUVFrame whiteFrame(40, 40, 255, 125, 125);

    int x = 13;
    int y = 13;

    for(int i = 0; i < 10; ++i)
    {
        if(i % 2 == 0)
            x = 13;
        else
            x = 53;
        for(int j = 0; j < 18; ++j)
        {
            board.InjectFrame(x, y, whiteFrame);
            x+=80;
        }
        y+=40;
    }

    board.ToFile("res/what.yuv");

    return EXIT_SUCCESS;
}