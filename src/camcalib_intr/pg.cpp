#include <iostream>
#include <unistd.h>
#include "opencv2/opencv.hpp"
#include "CalibUtils.hpp"

int main()
{
    std::string fileName = "cam1chess";
    std::string extension = ".png";
    std::string s = "sh rename.sh \"" + fileName + "\" \"" + extension + "\" \"input_data\"";

    std::cout << s.c_str() << std::endl;

    return 0;
}
