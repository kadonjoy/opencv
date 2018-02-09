/*
 **************************************************************************************
 *       Filename:  cv_compColor.cpp
 *    Description:
 *                1. introduce how to create lookup table
 *                2. for instance implement opencv time calculation
 *                3. compress color space
 *
 *        Version:  1.0
 *        Created:  2018-02-09 13:54:58
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

#define SRC_PIC "744x992_dst.jpg"

Mat& ScanImageAndReduceC(Mat& input, const uchar* table)
{
    CV_Assert(input.depth() != sizeof(uchar));

    int channels = input.channels();

    int rows = input.rows;
    int cols = input.cols*channels;

    if (input.isContinuous()) {
        cols *= rows;
        rows = 1;
    }

    int i, j;
    uchar* p;
    for (i = 0; i < rows; i++) {
        p = input.ptr<uchar>(i);
        for (j = 0; j < cols; j++) {
            p[j] = table[p[j]];
        }
    }

    return input;
}

Mat& ScanImageAndReduceIterator(Mat& input, const uchar* const table)
{
    CV_Assert(input.depth() != sizeof(uchar));

    const int channels = input.channels();

    switch(channels)
    {
        case 1:
        {
            MatIterator_<uchar> it, end;
            for( it = input.begin<uchar>(), end = input.end<uchar>(); it != end; ++it)
            {
                *it = table[*it];
            }
        }
        break;

        case 3:
        {
            MatIterator_<Vec3b> it, end;
            for( it = input.begin<Vec3b>(), end = input.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
        break;
    }

    return input;
}

Mat& ScanImageAndReduceRandomAccess(Mat& input, const uchar* const table)
{
    CV_Assert(input.depth() != sizeof(uchar));

    const int channels = input.channels();

    switch(channels)
    {
        case 1:
        {
            for (int i = 0; i < input.rows; i++) {
                for (int j = 0; j < input.cols; j++) {
                    input.at<uchar>(i,j) = table[input.at<uchar>(i,j)];
                }
            }
        }
        break;

        case 3:
        {
            Mat_<Vec3b> clone_img = input;
            for (int i = 0; i < input.rows; i++) {
                for (int j = 0; j < input.cols; j++) {
                     clone_img(i,j)[0] = table[clone_img(i,j)[0]];
                     clone_img(i,j)[1] = table[clone_img(i,j)[1]];
                     clone_img(i,j)[2] = table[clone_img(i,j)[2]];
                }
            }
        }
        break;
    }

    return input;
}

int main(int argc, char * argv[])
{
//    namedWindow("Org Picture", 1);
//    namedWindow("Changed Picture", 1);
    Mat srcImage, dstImage;

    srcImage = imread(SRC_PIC, CV_LOAD_IMAGE_COLOR);
    if (!srcImage.data) {
        cout << "Fail to load image: " << " " << SRC_PIC << endl;
        return -1;
    }

    int divideWith = 0;
    // convert string to integer
    stringstream s;
    s << "50";
    s >> divideWith;

    if (!s || !divideWith)  
    {  
        cout << "Invalid number entered for dividing. " << endl;  
        return -1;  
    }  

    uchar table[256];
    for (unsigned int i=0; i < sizeof(table); i++) {
        table[i] = (uchar)(divideWith * (i/divideWith));
    }

    //执行次数为100次  
    const int times = 100;  
    double t;  
  
    ////////////////////////////// C operator [] ////////////////////////////////
    t = (double)getTickCount();  
  
    for (int i = 0; i < times; ++i)  
    {  
        Mat clone_src = srcImage.clone();  
        dstImage = ScanImageAndReduceC(clone_src, table);  
    }  
    //计算100次的平均时间  
    t = 1000*((double)getTickCount() - t)/getTickFrequency();  
    t /= times;  
    //显示原图片和改变图片  
//    imshow("Org Picture", srcImage);
//    imshow("Changed Picture", dstImage);
//    waitKey(0);  
    imwrite("c-operator.jpg", dstImage);
    cout << "Time of reducing with the C operator [] (averaged for "  
        << times << " runs): " << t << " milliseconds."<< endl;  
    ////////////////////////////// C operator [] ////////////////////////////////


    /////////////////////////////// Iterator ////////////////////////////////////

    t = (double)getTickCount();  
  
    for (int i = 0; i < times; ++i)  
    {  
        Mat clone_src1 = srcImage.clone();  
        dstImage = ScanImageAndReduceIterator(clone_src1, table);  
    }  
  
    t = 1000*((double)getTickCount() - t)/getTickFrequency();  
    t /= times;  
  
    imwrite("iterator.jpg", dstImage);
    cout << "Time of reducing with the iterator (averaged for "  
        << times << " runs): " << t << " milliseconds."<< endl; 
    /////////////////////////////// Iterator ////////////////////////////////////


    /////////////////////////////// On the fly ////////////////////////////////////
    t = (double)getTickCount();  
  
    for (int i = 0; i < times; ++i)
    {  
        Mat clone_src2 = srcImage.clone();
        dstImage = ScanImageAndReduceRandomAccess(clone_src2, table);
    }
  
    t = 1000*((double)getTickCount() - t)/getTickFrequency();  
    t /= times;  
  
    imwrite("on_the_fly.jpg", dstImage);
    cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "  
        << times << " runs): " << t << " milliseconds."<< endl; 
    /////////////////////////////// On the fly ////////////////////////////////////

    ///////////////////////////////// LUT //////////////////////////////////
    Mat lookupMat(1,256, CV_8U);
    uchar *p = lookupMat.data;
    for (unsigned int i = 0; i < sizeof(table); i++) {
        p[i] = table[i];
    }

    t = (double)getTickCount();

    for (int i = 0; i < times; i++) {
        Mat clone_src3 = srcImage.clone();
        LUT(clone_src3, lookupMat, dstImage);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();  
    t /= times;  
      
    imwrite("lut.jpg", dstImage);
    cout << "Time of reducing with the LUT function (averaged for "  
        << times << " runs): " << t << " milliseconds."<< endl; 
    ///////////////////////////////// LUT //////////////////////////////////
//    imshow("Org Picture", srcImage);
//    waitKey(0);

    return 0;
}


/********************************** END **********************************************/

