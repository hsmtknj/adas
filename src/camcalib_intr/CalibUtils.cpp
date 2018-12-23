#include <iostream>
#include "CalibUtils.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


CalibUtils::CalibUtils()
{

}

CalibUtils::~CalibUtils()
{

}

bool CalibUtils::detectCorners(cv::Mat &inputImg,
                               cv::Size &patternsize,
                               std::string outputFileNameHead,
                               int outputImgId,
                               std::string extension,
                               std::vector<cv::Point2f> &detectedCorners,
                               cv::Mat &outputDrawnImg)
{
    // convert intput image into grayscaole image
    cv::Mat grayImg;
    cv::cvtColor(inputImg, grayImg, CV_BGR2GRAY);

    // find chess corners in a chessboard
    bool patternfound = findChessboardCorners(grayImg,
                                              patternsize,
                                              detectedCorners,
                                              cv::CALIB_CB_ADAPTIVE_THRESH |
                                              cv::CALIB_CB_NORMALIZE_IMAGE |
                                              cv::CALIB_CB_FAST_CHECK);
    
    if (patternfound)
    {
        // refine corners pixel position
        cv::cornerSubPix(grayImg,
                         detectedCorners,
                         cv::Size(11, 11),
                         cv::Size(-1, -1),
                         cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));                         
        
        // draw corners to output image
        outputDrawnImg = inputImg.clone();
        cv::drawChessboardCorners(outputDrawnImg, patternsize, cv::Mat(detectedCorners), patternfound);
    }

    return patternfound;
}
