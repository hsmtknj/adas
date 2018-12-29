#include <iostream>
#include "opencv2/opencv.hpp"
#include "../utils/CvUtil.hpp"

int main()
{
    cv::Size patternSize(8, 5);
    std::cout << patternSize.height << std::endl;
    std::cout << patternSize.width << std::endl;

    return 0;
}
