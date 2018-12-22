#include <iostream>
#include <unistd.h>
#include "opencv2/opencv.hpp"
#include "CalibUtils.hpp"

int main()
{
    // chess size
    cv::Size patternsize(8, 5);  // (width, height)
    std::vector<cv::Point2f> detected_corners;

    // load image
    std::string inputImgFile = "./data/cam1/cam1chess0.png";
    cv::Mat inputImg = cv::imread(inputImgFile, 1);

    // detect chessboard corners
    cv::Mat outputImg;
    bool b = CalibUtils::detectCorners(inputImg,
                             patternsize,
                             detected_corners,
                             0,
                             outputImg,
                             "./test");


    return 0;
}
