#ifndef INCLUDED_CALIBUTIL_HPP
#define INCLUDED_CALIBUTIL_HPP

#include <iostream>
#include "opencv2/opencv.hpp"

class CvUtil
{
    public:
        // constructor and destructor
        CvUtil();
        ~CvUtil();

        /**
         * @brief detect corners from multiple chessboard images
         */ 
        static bool detectCorners(cv::Mat &inputImg,
                                  cv::Size &patternsize,
                                  std::vector<cv::Point2f> &detectedCorners,
                                  cv::Mat &outputDrawnImg);

        /**
         * @brief save detected points
         */ 
        static void savePoint2f (std::vector<cv::Point2f> points, 
                                 std::string outputFileName);

        /**
         * @brief load points
         */ 
        static bool loadPoint2f (std::vector<cv::Point2f> &points,
                                 std::string filePath,
                                 char delim);

};

#endif