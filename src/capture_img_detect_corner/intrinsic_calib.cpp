#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"

int main()
{
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;

    // load points detected from a chessboard
    std::ifstream readPointsData("./data/cam1/foundcam1chess0.csv");
    if (!readPointsData)
    {
        std::cout << "ERROR: Input data file is not found." << std::endl;
        return -1;
    }

    std::string dataLineStr;
    int count = 0;
    while(getline(readPointsData, dataLineStr))
    {

    }


    return 0;
}
