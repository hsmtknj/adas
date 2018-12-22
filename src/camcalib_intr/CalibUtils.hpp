#ifndef INCLUDED_CALIBUTILS_HPP
#define INCLUDED_CALIBUTILS_HPP

#include <iostream>
#include "opencv2/opencv.hpp"

class CalibUtils
{
    public:
        // constructor and destructor
        CalibUtils();
        ~CalibUtils();

        // static functions
        static bool detectCorners(cv::Mat &inputImg,
                                  cv::Size &patternsize,
                                  std::vector<cv::Point2f> &detected_corners,
                                  int id,
                                  cv::Mat outputImg,
                                  std::string outputPath);
};

#endif