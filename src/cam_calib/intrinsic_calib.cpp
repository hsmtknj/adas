/**
 * @file intrinsic_calib.cpp
 * @brief compute intrinsic camera parameters and distorion parameters
 * 
 * [HOW TO USE]
 * Step1. set parameters in the "Set Params"
 * 
 * Step2. set points data and images that corners are successfully detected.
 *        in the "detected_data" directory.
 *          - You'd better use "detect_chesscorner.cpp" before using this
 *            program.
 * 
 * Step3. run this program
 *          - You can get intrinsic camera and distortion parameters.
 *            along with undistorted images.
 * 
 * [NOTE]
 * 
 */

#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "../utils/CvUtil.hpp"

int main()
{
    // ========================================================================
    // Set Params
    // ========================================================================

    const int IMG_WIDTH = 640;
    const int IMG_HEIGHT = 480;
    const int CHESS_WIDTH = 8;
    const int CHESS_HEIGHT = 5;
    const float CHESS_SIZE = 25;  // unit: [mm]
    char delim = ',';
    std::string computedPramExtension = ".yml";
    std::string detectedCornersExtension = ".csv";
    std::string imgExtension = ".png";
    std::string fileName = "gopro";
    std::string inputDir = "detected_data/renamed_data";
    std::string outputDir = "output_data";
    std::string inputFileNameHead = "./" + inputDir + "/found" + fileName;
    std::string outputParamFileName = "./" + outputDir + "/intrdist" + computedPramExtension;
    std::string outputImgUndistFileNameHead = "./" + outputDir + "/undist";


    // ========================================================================
    // Intrinsic Camera Calibration
    // ========================================================================

    cv::Size patternSize(CHESS_WIDTH, CHESS_HEIGHT);

    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;

    // load detected chessboard corner points
    std::vector<cv::Point2f> imagePointsOneChess;
    bool flagDataExistence = true;
    int imageCounter = 0;

    while (flagDataExistence)
    {
        // load points data
        std::string detectedPointsFile = inputFileNameHead + std::to_string(imageCounter) + detectedCornersExtension;
        flagDataExistence = CvUtil::loadPoint2f(imagePointsOneChess, detectedPointsFile, delim);

        // if the program load all data, this loop finishes.
        if (flagDataExistence == false)
        {
            break;
        }

        // add loaded points to imagePoints for intricsic camera calibration
        imagePoints.push_back(imagePointsOneChess);
        imageCounter++;
    }

    // define object points
    std::vector<cv::Point3f> objectPoijntsOneChess;
    for (int y = 0; y < patternSize.height; y++)
    {
        for (int x = 0; x < patternSize.width; x++)
        {
            cv::Point3f chessPoint = {(float)x * CHESS_SIZE, (float)y * CHESS_SIZE, 0};
            objectPoijntsOneChess.push_back(chessPoint);
        }
    }

    for (int i = 0; i < imagePoints.size(); i++)
    {
        objectPoints.push_back(objectPoijntsOneChess);
    }

    // compute intrinsic camera parameters and distotion parameters
    std::vector<cv::Mat> rvecs, tvecs;
    cv::Mat cameraMatrix(3, 3, CV_64F);
    cv::Mat distCoeffs(8, 1, CV_64F);
    cv::calibrateCamera(objectPoints, imagePoints, cv::Size(IMG_WIDTH, IMG_HEIGHT), cameraMatrix, distCoeffs, rvecs, tvecs);

    // save intrinsic camera parameters and distotion parameters
    cv::FileStorage fs(outputParamFileName, cv::FileStorage::WRITE);
    fs << "cameraMatrix" << cameraMatrix;
    fs << "distCoeffs" << distCoeffs;
    fs.release();

    // undistort source images
    int cnt = 0;
    while(1){
        cv::Mat imgSrc = cv::imread(inputFileNameHead + std::to_string(cnt) + imgExtension);
        if (imgSrc.empty() == true)
        {
            break;
        }
        cv::Mat imgUndist;
        cv::undistort(imgSrc, imgUndist, cameraMatrix, distCoeffs);
        cv::imwrite(outputImgUndistFileNameHead + std::to_string(cnt) + imgExtension, imgUndist);
        cnt++;
    }
    return 0;
}
