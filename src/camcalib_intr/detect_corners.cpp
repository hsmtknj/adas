#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


int main()
{
  // chess size
  cv::Size patternsize(8, 5); // (width, height)
  std::vector<cv::Point2f> detected_corners;

  // load image
  std::string inputImgFile = "./data/cam1/cam1chess0.png";
  // std::string inputImgFile = "../../data/samplechess/samplechess.png";
  cv::Mat img_src = cv::imread(inputImgFile, 1);
  // cv::imshow("test", img_src);
  // cv::waitKey(0);
  cv::Mat img_gray;
  cv::cvtColor(img_src, img_gray, CV_RGB2GRAY);

  // find chess corners in a chessboard
  bool patternfound = findChessboardCorners(img_gray,
                                            patternsize,
                                            detected_corners,
                                            cv::CALIB_CB_ADAPTIVE_THRESH |
                                                cv::CALIB_CB_NORMALIZE_IMAGE |
                                                cv::CALIB_CB_FAST_CHECK);

  // refine corners pixel position
  if (patternfound)
  {
    std::cout << "FOUND" << std::endl;
    cv::cornerSubPix(img_gray,
                     detected_corners,
                     cv::Size(11, 11),
                     cv::Size(-1, -1),
                     cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
  }

  // draw corners and save an image
  cv::drawChessboardCorners(img_src, patternsize, cv::Mat(detected_corners), patternfound);
  std::string outputImgFile = "./tmp_data/outchess.png";
  cv::imwrite(outputImgFile, img_src);

  // seve detected corners
  std::ofstream log;
  std::string outputCsvFile = "./tmp_data/detected_corners.csv";
  // trunc: if the same name file exists, overwrite
  log.open(outputCsvFile, std::ios::trunc);
  log << detected_corners;
  log.close();
}
