#include <iostream>
#include "opencv2/opencv.hpp"

int main()
{
    // ========================================================================
    // Set Params
    // ========================================================================

    const int CAM1_ID = 1;
    const int CAM2_ID = 2;
    const int IMG_WIDTH = 640;
    const int IMG_HEIGHT = 480;
    const int CAPTURE_FPS = 30;
    double flowEventInterval = 2000;  // [ms]
    std::string imgExtention = ".png";
    std::string headname1 = "/input_data/cam1chess";
    std::string headname2 = "/input_data/cam2chess";

    return 0;
}