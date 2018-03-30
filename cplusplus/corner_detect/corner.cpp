/*
 **************************************************************************************
 *       Filename:  corner.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-17 21:01:03
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define max_corners 100
using namespace cv;

int main( int argc, char** argv )
{
    int cornerCount=max_corners;
    CvPoint2D32f corners[max_corners];
    double qualityLevel = 0.05;
    double minDistance = 5;
    IplImage *srcImage = 0, *grayImage = 0, *corners1 = 0, *corners2 = 0;
    int i;
    CvScalar color = CV_RGB(255,0,0);
    cvNamedWindow( "image", 1 ); //创建显示窗口
    //加载一副图片
    srcImage = cvLoadImage("demo.jpg", 1);
    grayImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, 1);
    //将原图灰度化
    cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);
    //创建两个与原图大小相同的临时图像
    corners1= cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_32F, 1);
    corners2= cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_32F, 1);
    //角点检测
    cvGoodFeaturesToTrack (grayImage, corners1, corners2, corners,
    &cornerCount, qualityLevel, minDistance, 0);
    printf("num corners found: %d\n", cornerCount);
    //在原图中将角点标记出来
    if(cornerCount>0)
    {
        for (i=0; i <cornerCount;++i){
            cvCircle(srcImage, cvPoint((int)(corners[i].x), (int)(corners[i].y)), 8, color, 1, CV_AA, 0);
        }
    }
    cvShowImage( "image", srcImage );
    cvSaveImage("dst.jpg", srcImage);
    cvReleaseImage(&srcImage);
    cvReleaseImage(&grayImage);
    cvReleaseImage(&corners1);
    cvReleaseImage(&corners2);
    cvWaitKey(0);
    return 0;
}




/********************************** END **********************************************/

