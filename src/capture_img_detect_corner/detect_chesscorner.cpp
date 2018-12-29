/**
 * @file detect_chesscorner.cpp
 * @brief detect corners from multiple chessboard image
 * 
 * [HOW TO USE]
 * Step1. Set your chessboard images in the directory "./input_data/"
 *          You don't need to set files name to sequential order numbers.
 *          Following file names are OK.
 *              - chessboard0.png
 *              - chessboard3.png
 *              - chessboard4.png
 *          And you don't need to set images that corners points can be detected.
 *          In short, this program allows both type of images input that the 
 *          corners points can be detected and cannot be detected.
 * 
 * Step2. Set your parameters of "Settings"
 *          You check following parameters.
 *              - fileName
 *              - imgExtension
 *              - detectedCornersExtension
 *              - patternSize
 * 
 * Step3. Get detected corners points from "./output_data/" or "./ouput_data/renamed_data/"
 *          You can get detected points according to input IDs in the "./output_data/".
 *          And you can also get the points in the sequential order numbering files name.
 * 
 * [NOTE]
 * In this program, a shell script and commands are utilized.
 * So without the kind of an environment (e.g. bash), this program can provide errors.
 */

#include <iostream>
#include <unistd.h>
#include "opencv2/opencv.hpp"
#include "../utils/CvUtil.hpp"

int main()
{
    // ========================================================================
    // SET PARAMS
    // ========================================================================

    std::string fileName = "gopro";
    std::string inputDir = "input_data";
    std::string outputDir = "detected_data";
    std::string inputFileNameHead = "./" + inputDir + "/" + fileName;
    std::string outputFileNameHead = "./" + outputDir + "/found" + fileName;    
    std::string imgExtension = ".png";
    std::string detectedCornersExtension = ".csv";
    const int CHESS_WIDTH = 8;
    const int CHESS_HEIGHT = 5;


    // ========================================================================
    // Detect Corners
    // ========================================================================

    std::string cmd;
    
    // set chess size
    cv::Size patternSize(CHESS_WIDTH, CHESS_HEIGHT);
    std::vector<cv::Point2f> detectedCorners;

    // rename files in an input_data directory
    cmd = "sh rename.sh \"" + fileName + "\" \"" + imgExtension + "\" \"" + inputDir + "\"";
    system(cmd.c_str());

    // make a directory for input images that corners are detected
    cmd = "mkdir ./" + outputDir + "/original_img";
    system(cmd.c_str());

    // detect corners
    int imageCounter = 0;
    while(1)
    {
        // load image
        std::string inputImgFile = inputFileNameHead + std::to_string(imageCounter) + imgExtension;
        cv::Mat inputImg = cv::imread(inputImgFile, 1);
        if (inputImg.empty() == true)
        {
            break;
        }

        // detect chessboard corners
        cv::Mat outputDrawnImg;
        bool patternfound = CvUtil::detectCorners(inputImg,
                                                     patternSize,
                                                     outputFileNameHead,
                                                     imageCounter,
                                                     imgExtension,
                                                     detectedCorners,
                                                     outputDrawnImg);

        if (patternfound)
        {
            // save an output image that detected corners are drawn
            int outputImgId = imageCounter;
            std::string outputImgFile = outputFileNameHead + std::to_string(outputImgId) + imgExtension;
            cv::imwrite(outputImgFile, outputDrawnImg);

            // save detected corners
            std::string outputCsvFile = outputFileNameHead + std::to_string(outputImgId) + detectedCornersExtension;
            CvUtil::savePoint2f(detectedCorners, outputCsvFile);

            // copy an original input image to an output directory
            cmd = "cp " + inputImgFile + " ./" + outputDir + "/original_img/" + fileName + std::to_string(imageCounter) + imgExtension;
            system(cmd.c_str());
        }

        imageCounter++;
    }

    // rename files in an output_data directory (.png and .csv)
    cmd = "sh rename.sh \"found" + fileName + "\" \"" + imgExtension + "\" \"" + outputDir + "\"";
    system(cmd.c_str());
    cmd = "sh rename.sh \"found" + fileName + "\" \"" + detectedCornersExtension + "\" \"" + outputDir + "\"";
    system(cmd.c_str());

    // copy original input image that corners are detected to an output directory
    cmd = "sh rename.sh \"" + fileName + "\" \"" + imgExtension + "\" \"" + outputDir + "/original_img\"";
    system(cmd.c_str());
    cmd = "cp ./" + outputDir + "/original_img/renamed_data/*" + imgExtension + " ./" + outputDir + "/renamed_data/";
    system(cmd.c_str());
    cmd = "rm -r ./" + outputDir + "/original_img";
    system(cmd.c_str());

    return 0;
}
