/**
 * @file detect_corners_multiimg.cpp
 * @brief detect corners from multiple chessboard img
 * 
 * [HOW TO USE]
 * Step1. Set your chessboard images in the directory "./input_data/"
 *          You don't need to set files name to sequential order numbers.
 *          Following file names are OK.
 *              - chessboard0.png
 *              - chessboard3.png
 *              - chessboard4.png
 * 
 * Step2. Set your parameters of "Settings"
 *          You check following parameters.
 *              - fileName
 *              - imgExtension
 *              - detectedCornersExtension
 *              - patternsize
 * 
 * Step3. Get detected corners points from "./output_data/" or "./ouput_data/renamed_data/"
 *          You can get detected points according to input IDs in the "./output_data/".
 *          And you can also get the points in the sequential order numbering files name.
 * 
 * [NOTE]
 * In this program, a shell script and command is utilized.
 * So without the kind of an environment (e.g. bash), this program provides errors or something.
 */

#include <iostream>
#include <unistd.h>
#include "opencv2/opencv.hpp"
#include "CalibUtils.hpp"

int main()
{
    // ========================================================================
    // Settings
    // ========================================================================

    const int LOOP_NUM = 1000000000;
    std::string fileName = "cam1chess";
    std::string inputFileNameHead = "./input_data/" + fileName;
    std::string imgExtension = ".png";
    std::string detectedCornersExtension = ".csv";
    std::string outputFileNameHead = "./output_data/found" + fileName;

    // chess size
    cv::Size patternsize(8, 5); // (width, height)
    std::vector<cv::Point2f> detected_corners;


    // ========================================================================
    // Detect Corners
    // ========================================================================

    // rename files in an input_data directory
    std::string cmd = "sh rename.sh \"" + fileName + "\" \"" + imgExtension + "\" \"input_data\"";
    system(cmd.c_str());

    // make a directory for input images that corners are detected
    system("mkdir ./output_data/original_img");

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

            // copy an original input image to an output directory
            cmd = "cp " + inputImgFile + " ./output_data/original_img/" + fileName + std::to_string(i) + imgExtension;
            system(cmd.c_str());
        }
    }

    // rename files in an output_data directory (.png and .csv)
    cmd = "sh rename.sh \"found" + fileName + "\" \"" + imgExtension + "\" \"output_data\"";
    system(cmd.c_str());
    cmd = "sh rename.sh \"found" + fileName + "\" \"" + detectedCornersExtension + "\" \"output_data\"";
    system(cmd.c_str());

    // copy original input image that corners are detected to an output directory
    cmd = "sh rename.sh \"" + fileName + "\" \"" + imgExtension + "\" \"output_data/original_img\"";
    system(cmd.c_str());
    system("cp ./output_data/original_img/renamed_data/*.png ./output_data/renamed_data/");
    system("rm -r ./output_data/original_img");

    return 0;
}
