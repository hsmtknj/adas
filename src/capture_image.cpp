#include <iostream>
#include "opencv2/opencv.hpp"

int main()
{
    // set a camera
    cv::VideoCapture cap(1);
    // on failure to recognize a camera device
    if(!cap.isOpened())
    {
        return -1;
    }

    // processing
    while(1)
    {
        // get a new frame from a camera
        cv::Mat frame;
        cap >> frame;

        cv::imshow("window", frame);

        int key = cv::waitKey(1);
        // in the case of pushing "q" key
        if(key == 113)
        {
            // finish processing
            break;
        }
        // in the case of pushing "s" key
        else if(key == 115)
        {
            // save an image
            cv::imwrite("img.png", frame);
        }
    }
    cv::destroyAllWindows();
    return 0;
}