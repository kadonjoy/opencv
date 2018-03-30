/*
 **************************************************************************************
 *       Filename:  main_corner.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-29 14:15:42
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <stdlib.h>
#include <iostream>
#include <opencv2/core/core.hpp>                                                                                                                                                    
#include <opencv2/imgproc/imgproc.hpp>                                                                                                                                              
#include <opencv2/calib3d/calib3d.hpp>                                                                                                                                              
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

bool compare_point(Point2f x, Point2f y)
{
    if (x.y > y.y)
        return true;
    else
        return false;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    
    if ( argc <= 1 ) {
        cout    << "please input correct image name!" << endl;
        return EXIT_FAILURE;
    }
    Mat img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Size boardSize = Size(9,6);
    vector<Point2f> pointBuf;

    bool found = findChessboardCorners( img, boardSize, pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
    cout << "found: " << found << endl;
    if ( found ) {
        Mat imgGray;
        cvtColor(img, imgGray, COLOR_RGB2GRAY);
//        cout << pointBuf << endl;
        drawChessboardCorners(img, boardSize, pointBuf, found);
    }

    namedWindow("corner detect", 1);
    imshow("corner detect", img);
    waitKey(0);

    return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */

/********************************** END **********************************************/

