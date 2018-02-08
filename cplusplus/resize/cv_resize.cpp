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
//    int resize_height = 3584;
//    int resize_width = 2016;
    cv::Mat src = cv::imread(src_path); 
    sprintf(dst_file_name, "%dx%d_dst.jpg", src.cols/2, src.rows/2);
    cv::Mat dst;
    imshow("src", src);
    // downscale to 1/2 size
    cv::resize(src, dst, cv::Size(src.cols/2, src.rows/2), 0, 0, cv::INTER_LINEAR);
    imshow("dst", dst);
    imwrite(dst_file_name, dst);
    cv::waitKey(0);

    return 0;
}



/********************************** END **********************************************/

