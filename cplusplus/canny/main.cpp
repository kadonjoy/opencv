/*
 **************************************************************************************
 *       Filename:  show.cpp
 *    Description:  use opencv to show one jpg
 *
 *        Version:  1.0
 *        Created:  2017-08-30 17:45:54
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <cstdlib>
#include <fstream>
#include <iomanip>   
#include <iostream>   
#include <opencv/cv.h>
#include <opencv/highgui.h>
   

using namespace std;
using namespace cv;

// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  main function
// =====================================================================================
int main( int argc, char *argv[] )  
{
    Mat src, src_gray;
    Mat dst, detected_edges;
    int lowThreshold = 100;  
    int ratio = 3;  
    int kernel_size = 3;  
    const char* window_name = "Edge Map";  

    src = imread( argv[1] );  
    if( !src.data )  
        { return -1; }  
    dst.create( src.size(), src.type() );  
    cvtColor( src, src_gray, CV_BGR2GRAY );  
    namedWindow( window_name, WINDOW_NORMAL);  
    /// Reduce noise with a kernel 3x3  
    blur( src_gray, detected_edges, Size(3,3) );  
//    imshow( window_name, detected_edges );  
    /// Canny detector  
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );  
    dst = Scalar::all(0);  
    src.copyTo( dst, detected_edges);  
    imshow( window_name, dst );  
    waitKey(0);  

    return 0;  
}


/********************************** END **********************************************/

