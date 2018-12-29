#include <iostream>
#include <unistd.h>
#include "opencv2/opencv.hpp"

int main()
{
    // ========================================================================
    // SET PARAMS
    // ========================================================================

    const int CAM_ID = 0;
    const int IMG_WIDTH = 640;
    const int IMG_HEIGHT = 480;
    const int CAPTURE_FPS = 30;
    double flowEventInterval = 2000;  // [ms]
    std::string imgExtention = ".png";
    std::string headname = "/input_data/sample";


    // ========================================================================
    // PROC
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
    int captureCounter = 0;
    bool flagCaptureStart = false;
    std::string filename;
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
            filename = currentDirPath + headname + std::to_string(captureCounter) + imgExtention;
            std::cout << filename << std::endl;
            cv::imwrite(filename, frame);
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
            filename = currentDirPath + headname + std::to_string(captureCounter) + imgExtention;
            std::cout << filename << std::endl;
            cv::imwrite(filename, frame);
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