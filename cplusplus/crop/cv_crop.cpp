/*
 **************************************************************************************
 *       Filename:  cv_crop.cpp
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
    int height_16_9 = 3584;
    int width_16_9 = 2016;
    sprintf(dst_file_name, "%dx%d_dst.jpg", width_16_9, height_16_9);
    cv::Mat src_img = cv::imread(src_path); 
    int startX=(src_img.cols-width_16_9)/2, startY=(src_img.rows-height_16_9)/2;
    cv::Mat ROI(src_img, cv::Rect(startX,startY,width_16_9,height_16_9));
    cv::Mat croppedImage;
    // Copy the data into new matrix
    ROI.copyTo(croppedImage);
    imwrite(dst_file_name, croppedImage);

    cv::waitKey(0);

    return 0;
}



/********************************** END **********************************************/

