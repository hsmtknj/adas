#include <iostream>
#include "../utils/CvUtil.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


CvUtil::CvUtil()
{

}

CvUtil::~CvUtil()
{

}

/**
 * @CvUtil::detectCorners
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
bool CvUtil::detectCorners(cv::Mat &inputImg,
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
 * @CvUtil::savePoints2f
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
void CvUtil::savePoint2f(std::vector<cv::Point2f> points,
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

/**
 * @CvUtil::loadPoints2f
 * 
 * @brief load as cv::Point2f
 * [INPUT]
 * @param (filePath) file path you want to load
 * @param (delim) delimiter e.g. ','
 * [OUTPUT]
 * @param (points) loaded points
 * @return 
 * @sa
 * @detail
 *  load points
 */
bool CvUtil::loadPoint2f(std::vector<cv::Point2f> &points,
                         std::string filePath,
                         char delim)
{
    // initialize
    bool flagLoaded = true;
    points.clear();

    // open a file
    std::ifstream pointsData(filePath);
    if (!pointsData)
    {
        flagLoaded = false;
        return flagLoaded;
    }

    // extract number from an opened file
    std::string strLine;
    int count = 0;
    while(std::getline(pointsData, strLine))
    {
        std::string extractedTarget;
        std::istringstream stream(strLine);
        count = 0;
        float x, y;
        while(std::getline(stream, extractedTarget, delim))
        {
            if (count == 0)
            {
                x = std::stof(extractedTarget);
            }
            else if (count == 1)
            {
                y = std::stof(extractedTarget);
            }
            count++;
        }
        cv::Point2f extractedPoints = {x, y};
        points.push_back(extractedPoints);
    }

    return flagLoaded;
}
