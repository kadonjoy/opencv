/*
 **************************************************************************************
 *       Filename:  gaussian_main.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-20 11:02:13
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

using namespace std;

int main()
{
    IplImage* srcImg = cvLoadImage("../../images/2976x3968.jpg");
    IplImage* tmpImg = cvCreateImage(cvSize(500,500),8,3); 
    IplImage* grayImg = cvCreateImage(cvSize(500,500),8,1); 
    IplImage* dstImg = cvCreateImage(cvSize(500,500),8,1); 
//    IplImage* dstImg = cvCreateImage(cvSize(srcImg->width, srcImg->height),8,3); 

    cvResize(srcImg, tmpImg);
    cvCvtColor(tmpImg, grayImg, CV_BGR2GRAY);
    cvNamedWindow("src");
    cvNamedWindow("Gaussian Filter");
    
    // sigma=0.8
    cvSmooth(grayImg, dstImg, CV_GAUSSIAN, 3, 3, 0.8);
//    cvSmooth(srcImg, dstImg, CV_GAUSSIAN, 3, 3, 0.8);

    cvShowImage("src", grayImg);
//    cvShowImage("src", srcImg);
    cvShowImage("Gaussian Filter", dstImg);

    cvWaitKey(50000);

    cvReleaseImage(&srcImg);
    cvReleaseImage(&tmpImg);
    cvReleaseImage(&grayImg);
    cvReleaseImage(&dstImg);
    cvDestroyAllWindows();

    return 0;
}

/********************************** END **********************************************/

