#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"

int main()
{
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;

    // load points detected from a chessboard
    std::ifstream readPointsData("./output_data/renamed_data/foundcam1chess0.csv");
    if (!readPointsData)
    {
        std::cout << "ERROR: Input data file is not found." << std::endl;
        return -1;
    }

    std::string dataLineStr;
    std::vector<std::vector<float>> mat;
    std::vector<float> tmpVec;
    while(std::getline(readPointsData, dataLineStr))
    {
        std::string token;
        std::istringstream stream(dataLineStr);
        while(std::getline(stream, token, ','))
        {
            std::cout << token << std::endl;
        }
    }



    return 0;
}
