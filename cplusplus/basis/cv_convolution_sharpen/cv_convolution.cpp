/*
 **************************************************************************************
 *       Filename:  cv_convolution.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-02-09 16:45:31
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 
#include <iostream>

using namespace std;
using namespace cv;

#define SRC_PIC "../744x992_dst.jpg"

void custom_sharpen(const Mat& input, Mat& output)
{
    CV_Assert(input.depth() == CV_8U);
    output.create(input.size(), input.type());
    int n_channels = input.channels();

    // The first and last row doesn't participate in the calculation 
    for (int i = 1; i < input.rows - 1; i++) {
        const uchar* previous_line = input.ptr<uchar>(i-1);
        const uchar* current_line = input.ptr<uchar>(i);
        const uchar* next_line = input.ptr<uchar>(i+1);
        
        uchar * out_ptr = output.ptr<uchar>(i);
        // The first and last col doesn't participate in the calculation 
        for (int j = n_channels; j < n_channels*(input.cols-1); j++) {
            *out_ptr++ = saturate_cast<uchar>(5*current_line[j] - previous_line[j] - next_line[j] 
                - current_line[j - n_channels] - current_line[j + n_channels]);
        }
    }

    output.row(0).setTo(Scalar(0));
    output.row(output.rows-1).setTo(Scalar(0));
    output.col(0).setTo(Scalar(0));
    output.col(output.cols-1).setTo(Scalar(0));
}

int main(int argc, char * argv[])
{
    Mat srcImage, dstImage1, dstImage2;

    srcImage = imread(SRC_PIC, CV_LOAD_IMAGE_COLOR);
    if (!srcImage.data) {
        cout << "Fail to load image: " << " " << SRC_PIC << endl;
        return -1;
    }
    
    double t;
    t = (double)getTickCount();

    // call custom sharpen function
    custom_sharpen(srcImage, dstImage1);
    imwrite("custom_sharpen.jpg", dstImage1);

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    cout << "Time of manual sharpen :  " << t << "milliseconds." << endl;

    Mat kern = (Mat_<char>(3,3) <<  0, -1,  0,  
                    -1,  5, -1,  
                    0, -1,  0);  
    t = (double)getTickCount();  
    filter2D(srcImage, dstImage2, srcImage.depth(), kern );//使用滤波器掩码函数  
    t = ((double)getTickCount() - t)/getTickFrequency();
    imwrite("filter2D.jpg", dstImage2);
    cout << "Built-in filter2D time passed in seconds:      " << t << endl; 

    return 0;
}

/********************************** END **********************************************/
