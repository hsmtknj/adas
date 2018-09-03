#include <iostream>
#include <Eigen/Dense>
#include "opencv2/opencv.hpp"

int main()
{
    std::vector<cv::Point2f> vp;
    cv::Point2f p;
    p.x = 0;
    p.y = 1;
    vp.push_back(p);
    p.x = 2;
    p.y = 3;
    vp.push_back(p);
    std::cout << vp << std::endl;

    Eigen::MatrixXd mat(2, 2);
    mat.setZero();
    std::cout << mat << std::endl;
}
