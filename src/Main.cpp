#include <iostream>
#include "Bitmap.h"

int main(int argc, char **argv)
{
    try
    {
        Bitmap bmp("res/1.bmp");
        bmp.ToFile("res/hihi.bmp");
    }
    catch(const char* e)
    {
        std::cerr << e << '\n';
    }

    return EXIT_SUCCESS;
}