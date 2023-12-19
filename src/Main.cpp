#include <iostream>
#include <fstream>
#include <string>
#include "Bitmap.h"
#include "YUVFrame.h"
#include "Convertion.h"

int main(int argc, char **argv)
{
    if(argc < 5)
    {
        std::cout << "input: name.bmp X.Y name.yuv W.H\n";
        return EXIT_SUCCESS;
    }

    try
    {
        Bitmap bmp(argv[1]);
        YUVFrame picture = BMPToYUV(bmp, true);

        std::ifstream input(argv[3], std::ios::binary);
        std::ofstream output("out.yuv", std::ios::binary);

        std::string xy(argv[2]);

        int pos = xy.find('.');
        int x = atoi(xy.substr(0, pos).c_str()); 
        int y = atoi(xy.substr(pos + 1, xy.size()).c_str()); 

        std::string wxh(argv[4]);

        pos = wxh.find('.');
        int width = atoi(wxh.substr(0, pos).c_str()); 
        int height = atoi(wxh.substr(pos + 1, wxh.size()).c_str()); 

        YUVFrame frame(width, height, 255, 125, 125);

        while(!input.eof())
        {
            frame.ReadFile(input);
            frame.InjectFrame(x, y, picture);
            frame.ToFile(output);
        }

        input.close();
        output.close();
    }
    catch(const char* e)
    {
        std::cerr << e << '\n';
    }

    return EXIT_SUCCESS;
}