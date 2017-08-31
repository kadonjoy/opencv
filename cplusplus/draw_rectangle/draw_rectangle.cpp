/*
 **************************************************************************************
 *       Filename:  draw_rectangle.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2017-08-31 17:47:20
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
int main ( int argc, char *argv[] )
{
    Mat drawPaper(600, 600, CV_8UC3, Scalar(0));
    RotatedRect rRect = RotatedRect(Point2f(300, 300), Size2f(300, 300), 70);
    Point2f vertices[4];
    rRect.points(vertices);
    for (int i = 0; i < 2; i++) {
        // draw one read line with two point
        line(drawPaper, vertices[i], vertices[(i+2)%4], Scalar(0, 0, 255));
        cout << "vertice: " << vertices[i] << endl;
    }
    Rect brect = rRect.boundingRect();
    // draw one blue rectangle
    rectangle(drawPaper, brect, Scalar(255,0,0));

    imshow("drawing paper", drawPaper);

    // 普及矩阵基础知识
    Matx33f m(1, 2, 3,
            4, 5, 6,
            7, 8, 9);
//    cout << m << endl;
//    cout << sum(Mat(m*m.t())) << endl;
//    cout << m*m.t() << endl;
    // 打印矩阵的转置
    cout << m.t() << endl;
    cout << Mat(m*m.t()) << endl;

    waitKey(0);

	return EXIT_SUCCESS;
}		// ----------  end of function main  ---------- 

/********************************** END **********************************************/

