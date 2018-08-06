#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

// global variables
std::string filename = "";

int main()
{
  // chess size
  cv::Size patternsize(8, 5);  // (width, height)
  std::vector<cv::Point2f> detected_corners;

  // load image
  filename = "./samplechess.png";
  cv::Mat img_src = cv::imread(filename, 1);
  cv::Mat img_gray;
  cv::cvtColor(img_src, img_gray, CV_RGB2GRAY);

  // fine chess corners in a chessboard
  bool patternfound = findChessboardCorners(img_gray,
                                            patternsize,
                                            detected_corners,
                                            cv::CALIB_CB_ADAPTIVE_THRESH |
                                                cv::CALIB_CB_NORMALIZE_IMAGE |
                                                cv::CALIB_CB_FAST_CHECK);

  // refine corners pixel position
  if (patternfound)
    cv::cornerSubPix(img_gray,
                     detected_corners,
                     cv::Size(11, 11),
                     cv::Size(-1, -1),
                     cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));

  // draw corners and save an image
  cv::drawChessboardCorners(img_src, patternsize, cv::Mat(detected_corners), patternfound);
  filename = "./outchess.png";
  cv::imwrite(filename, img_src);
}
