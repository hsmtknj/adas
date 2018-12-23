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

        /**
         * @CalibUtils::detectCorners
         * 
         * @brief detect corners from a chessboard
         * [INPUT]
         * @param (inputImg) an input image (NOTE: This must be RGB IMAGE.)
         * @param (patternsize) a pattern size of a target chessboard
         * @param (outputFileNameHead) path and file name of output image
         * @param (outputImgId) output image id number
         * @param (extension) a type of extension
         * [OUTPUT]
         * @param (detectedCorners) detected corners points from a chessboard image
         * @param (outputDrawnImg) an output image that detected corners are drawn
         * @return (patternfound) a flag that corners are successfully detected
         * @sa
         * @detail
         *  This function provides corners detection from a chessboard.
         *  If chessboard corners are detected, you can get "detectedCorners"
         *  and "outputDrawnImg" as output.
         */
        // TODO: enhance input image type (gray image acception)
        //          Currently an input image must be RGB image.
        static bool detectCorners(cv::Mat &inputImg,
                                  cv::Size &patternsize,
                                  std::string outputFileNameHead,
                                  int outputImgId,
                                  std::string extension,
                                  std::vector<cv::Point2f> &detectedCorners,
                                  cv::Mat &outputDrawnImg);
};

#endif