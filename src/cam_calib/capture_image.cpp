/**
 * @file capture_image.cpp
 * @brief capture images
 * 
 * [HOW TO USE]
 * Step1. set parameters in the "Set Params"
 * 
 * Step2. capture images
 *          There are two modes.
 *          <MODE1>
 *              - press "s" and you can get a sigle image.
 *          <MODE2>
 *              - press "b" and you can get images in the same interval.
 * 
 * [NOTE]
 * If you press "q", this program quits.
 */

#include <iostream>
#include <unistd.h>
#include "opencv2/opencv.hpp"

int main()
{
    // ========================================================================
    // Set Params
    // ========================================================================

    const int CAM_ID = 1;
    const int IMG_WIDTH = 640;
    const int IMG_HEIGHT = 480;
    const int CAPTURE_FPS = 30;
    int captureCounter = 0;
    double flowEventInterval = 2000;  // [ms]
    std::string fname = "cam1chess";
    std::string imgExtention = ".png";
    std::string captionDir = "/input_data/";


    // ========================================================================
    // Capture Images
    // ========================================================================

    // get cerrent diretory path
    char currentDirPath[255];
    getcwd(currentDirPath, 255);

    // set parameters for flow-driven processing
    int fps = 0;
    int frameCounter = 0;
    int frameCounterPre = 0;
    int64 currentTime = 0;
    int64 elapsedTime = 0;
    int64 startTime = cv::getTickCount();
    const double f = (1000 / cv::getTickFrequency());  // unit: micro -> milli

    // set camera parameters
    // <http://opencv.jp/opencv-2svn/cpp/reading_and_writing_images_and_video.html>
    cv::VideoCapture cap(CAM_ID);
    cap.set(CV_CAP_PROP_FPS, CAPTURE_FPS);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, IMG_WIDTH);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, IMG_HEIGHT);

    // on failure to recognize a camera device
    if(!cap.isOpened())
    {
        return -1;
    }

    // processing
    bool flagCaptureStart = false;
    while(1)
    {
        // get a new frame from a camera
        cv::Mat frame;
        cap >> frame;

        // show image
        cv::imshow("window", frame);

        // get and compute time
        currentTime = cv::getTickCount();  
        elapsedTime = (int)((currentTime - startTime) * f);


        // ====================================================================
        // flow-driven processing
        // ====================================================================

        frameCounter++;

        if (elapsedTime >= flowEventInterval && flagCaptureStart == true)
        {
            // save an image
            std::string filePath = currentDirPath + captionDir + fname + std::to_string(captureCounter) + imgExtention;
            std::cout << filePath << std::endl;
            cv::imwrite(filePath, frame);
            captureCounter++;

            // updated paramters
            startTime = currentTime;
            frameCounterPre = frameCounter;
        }

        // // show fps
        // if (elapsedTime >= flowEventInterval)
        // {
        //     // show fps
        //     fps = frameCounter - frameCounterPre;
        //     std::cout << fps << std::endl;

        //     // uptedate paramters
        //     startTime = currentTime;
        //     frameCounterPre = frameCounter;
        // }


        // ====================================================================
        // key event-driven processing
        // ====================================================================

        int key = cv::waitKey(1);

        // in the case of pushing "q" key
        if(key == 113)
        {
            // quit processing
            break;
        }
        // in the case of pushing "s" key
        else if(key == 115)
        {
            // save an image
            std::string filePath = currentDirPath + captionDir + fname + std::to_string(captureCounter) + imgExtention;
            std::cout << filePath << std::endl;
            cv::imwrite(filePath, frame);
            captureCounter++;
        }
        // in the case of pushing "b" key
        else if (key == 98)
        {
            // change flag to begin capture
            flagCaptureStart = true;
        }

    }

    cv::destroyAllWindows();
    return 0;
}