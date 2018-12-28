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
 * @brief detect corners from multiple chessboard images
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
// TODO: enhance an input image type (gray image acception)
//          Currently an input image must be RGB image.
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

/**
 * @CalibUtils::savePoints2f
 * 
 * @brief save std::vector<cv::Point2f>
 * [INPUT]
 * @param (points) cv::Point2f points
 * [OUTPUT]
 * @param (outputFileName) a file name and path of saved points
 * @return 
 * @sa
 * @detail
 *  save points
 */
void CalibUtils::savePoint2f (std::vector<cv::Point2f> points,
                              std::string outputFileName)
{
    std::ofstream ofs;

    // [option] trunc: if the same name file exists, overwrite
    ofs.open(outputFileName, std::ios::trunc);
    for (int i = 0; i < points.size(); i++)
    {
        ofs << points[i].x << "," << points[i].y << "\n";
    }
    ofs.close();
}                         
                            
