/*
 **************************************************************************************
 *       Filename:  cv_resize.cpp
 *    Description:  source file
 *
 *        Version:  1.0
 *        Created:  2018-02-08 15:33:52
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char** argv)
{
    std::string src_path = "2976x3968.jpg";
    char dst_file_name[20]; 
    cv::Mat src = cv::imread(src_path); 
    int resize_height = src.rows/4;
    int resize_width = src.cols/4;
    sprintf(dst_file_name, "%dx%d_dst.jpg", resize_width, resize_height);
    cv::Mat dst;
    imshow("src", src);
    // downscale to 1/2 size
    cv::resize(src, dst, cv::Size(resize_width, resize_height), 0, 0, cv::INTER_LINEAR);
    imshow("dst", dst);
    imwrite(dst_file_name, dst);
    cv::waitKey(0);

    return 0;
}



/********************************** END **********************************************/

