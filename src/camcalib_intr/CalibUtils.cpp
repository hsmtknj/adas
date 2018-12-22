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

/**
 * @CalibUtils::detectCorners
 * 
 * @brief detect corners from a chessboard
 * @param (inputImg)
 * @param (patternsize)
 * @param (detected_corners)
 * @param (outputImg)
 * @return 
 * @sa
 * @detail
 * hogehoge
 */
bool CalibUtils::detectCorners(cv::Mat &inputImg,
                               cv::Size &patternsize,
                               std::vector<cv::Point2f> &detected_corners,
                               int outputImgId,
                               cv::Mat outputImg,
                               std::string outputPath)
{
    // convert intput image into grayscaole image
    cv::Mat grayImg;
    cv::cvtColor(inputImg, grayImg, CV_BGR2GRAY);

    // find chess corners in a chessboard
    bool patternfound = findChessboardCorners(grayImg,
                                              patternsize,
                                              detected_corners,
                                              cv::CALIB_CB_ADAPTIVE_THRESH |
                                              cv::CALIB_CB_NORMALIZE_IMAGE |
                                              cv::CALIB_CB_FAST_CHECK);
    
    if (patternfound)
    {
        // refine corners pixel position
        cv::cornerSubPix(grayImg,
                         detected_corners,
                         cv::Size(11, 11),
                         cv::Size(-1, -1),
                         cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));                         
        
        // draw corners and save an image
        cv::Mat drawnImg = inputImg.clone();
        cv::drawChessboardCorners(drawnImg, patternsize, cv::Mat(detected_corners), patternfound);
        std::string outputImgFile = outputPath + std::to_string(outputImgId) + ".png";
        cv::imwrite(outputImgFile, drawnImg);

        // seve detected corners
        std::ofstream log;
        std::string outputCsvFile = outputPath + std::to_string(outputImgId) + ".csv";
        // trunc: if the same name file exists, overwrite
        log.open(outputCsvFile, std::ios::trunc);
        log << detected_corners;
        log.close();
    }

    return patternfound;
}
