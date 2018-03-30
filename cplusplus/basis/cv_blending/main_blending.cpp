/*
 **************************************************************************************
 *       Filename:  main_blending.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-27 09:08:47
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    double alpha = 0.5, beta, input;

    Mat src1, src2, dst;

    cout << " Simple Linear Blender " << endl;
    cout << " --------------------- " << endl;
    cout << " * Enter alpha [0-1]: ";
    cin >> input;
    if( input >=0.0 && input < 1.0)
        alpha = input;
    cout << "alpha: " << alpha << endl;

    src1 = imread("1.jpg");
    src2 = imread("2.jpg");

    // create window
    namedWindow("Blend", 1);

    beta = 1.0 - alpha;

    addWeighted(src1, alpha, src2, beta, 0.0, dst);

    imshow("Blend", dst);

    waitKey(0);

    return 0;
}

/********************************** END **********************************************/
