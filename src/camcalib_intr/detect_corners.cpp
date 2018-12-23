#include <iostream>
#include <unistd.h>
#include "opencv2/opencv.hpp"
#include "CalibUtils.hpp"

int main()
{
    // settings
    const int LOOP_NUM = 1000000000;
    std::string fileName = "cam1chess";
    std::string inputFileNameHead = "./input_data/" + fileName;
    std::string imgExtension = ".png";
    std::string detectedCornersExtension = ".csv";
    std::string outputFileNameHead = "./output_data/found" + fileName;

    // chess size
    cv::Size patternsize(8, 5); // (width, height)
    std::vector<cv::Point2f> detected_corners;

    // rename files in an input_data directory
    std::string cmd = "sh rename.sh \"" + fileName + "\" \"" + imgExtension + "\" \"input_data\"";
    system(cmd.c_str());

    // detect corners
    for (int i = 0; i < LOOP_NUM; i++)
    {
        // load image
        std::string inputImgFile = inputFileNameHead + std::to_string(i) + imgExtension;
        cv::Mat inputImg = cv::imread(inputImgFile, 1);
        if (inputImg.empty() == true)
        {
            break;
        }

        // detect chessboard corners
        cv::Mat outputDrawnImg;
        bool patternfound = CalibUtils::detectCorners(inputImg,
                                                      patternsize,
                                                      outputFileNameHead,
                                                      i,
                                                      imgExtension,
                                                      detected_corners,
                                                      outputDrawnImg);

        if (patternfound)
        {
            // save an output image that detected corners are drawn
            int outputImgId = i;
            std::string outputImgFile = outputFileNameHead + std::to_string(outputImgId) + imgExtension;
            cv::imwrite(outputImgFile, outputDrawnImg);

            // seve detected corners
            std::ofstream log;
            std::string outputCsvFile = outputFileNameHead + std::to_string(outputImgId) + detectedCornersExtension;
            // trunc: if the same name file exists, overwrite
            log.open(outputCsvFile, std::ios::trunc);
            log << detected_corners;
            log.close();
        }
    }

    // rename files in an output_data directory (.png and .csv)
    cmd = "sh rename.sh \"found" + fileName + "\" \"" + imgExtension + "\" \"output_data\"";
    system(cmd.c_str());
    cmd = "sh rename.sh \"found" + fileName + "\" \"" + detectedCornersExtension + "\" \"output_data\"";
    system(cmd.c_str());

    return 0;
}
