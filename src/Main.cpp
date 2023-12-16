#include <iostream>
#include <fstream>
#include "Bitmap.h"
#include "YUVFrame.h"

int main(int argc, char **argv)
{

    YUVFrame board(640, 360, 0, 125, 125);
    
    YUVFrame whiteFrame(40, 40, 255, 125, 125);

    int x = 1;
    int y = 1;

    board.InjectFrame(200, 200, whiteFrame); //correct
    board.InjectFrame(80, 10, whiteFrame); //x!=y => uncorrect
/*
    for(int j = 0; j < 9; ++j)
    {
        board.InjectFrame(x, y, whiteFrame);
        x+=41;
    }
*/
/*
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
            board.InjectFrame(x, y, whiteFrame);
            x+=40;
        }
        y+=40;
    }
*/
    board.ToFile("res/what.yuv");

    return EXIT_SUCCESS;
}