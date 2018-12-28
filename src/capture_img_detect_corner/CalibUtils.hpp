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

        /**
         * @brief detect corners from multiple chessboard images
         */ 
        static bool detectCorners(cv::Mat &inputImg,
                                  cv::Size &patternsize,
                                  std::string outputFileNameHead,
                                  int outputImgId,
                                  std::string extension,
                                  std::vector<cv::Point2f> &detectedCorners,
                                  cv::Mat &outputDrawnImg);

        /**
         * @brief save detected points
         */ 
        static void savePoint2f (std::vector<cv::Point2f> points, 
                                 std::string outputFileName);

};

#endif