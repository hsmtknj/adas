#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "../utils/CvUtil.hpp"

int main()
{
    const float CHESS_SIZE = 25;  // unit: [mm]
    const int IMG_WIDTH = 640;
    const int IMG_HEIGHT = 480;
    cv::Size patternSize(8, 5); // (width, height)

    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;

    // load detected chessboard corner points
    std::vector<cv::Point2f> imagePointsOneChess;
    bool flagDataExistence = true;
    int imageCounter = 0;
    while (flagDataExistence)
    {
        // load points data
        std::string filePath = "./output_data/renamed_data/foundgopro" + std::to_string(imageCounter) + ".csv";
        flagDataExistence = CvUtil::loadPoint2f(imagePointsOneChess, filePath, ',');

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

    // // save intrinsic camera parameters and distotion parameters
    // cv::FileStorage fs("./intrdist.yml", cv::FileStorage::WRITE);
    // fs << "cameraMatrix" << cameraMatrix;
    // fs << "distCoeffs" << distCoeffs;
    // fs.release();

    // test
    int cnt = 0;
    while(1){
        cv::Mat imgSrc = cv::imread("./output_data/renamed_data/foundgopro" + std::to_string(cnt) + ".png");
        if (imgSrc.empty() == true)
        {
            break;
        }
        cv::Mat imgUndist;
        cv::undistort(imgSrc, imgUndist, cameraMatrix, distCoeffs);

        cv::imwrite("./test/undist" + std::to_string(cnt) + ".png", imgUndist);

        // cv::imshow("imgSrc", imgSrc);
        // cv::waitKey(1000);
        // cv::imshow("imgUndist", imgUndist);
        // cv::waitKey(1000);
        // cv::destroyAllWindows();

        cnt++;
    }
    return 0;
}
