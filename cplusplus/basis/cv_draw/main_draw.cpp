/*
 **************************************************************************************
 *       Filename:  main_draw.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-27 11:04:40
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 

using namespace cv;
using namespace std;

#define w 400

void Test_Ellipse(Mat img, double angle);
void Test_FilledCircle(Mat img, Point center);
void Test_Polygon(Mat img);
void Test_Line(Mat img, Point start, Point end);

int main(int argc, char** argv)
{
    char atom_name[] = "Drawing 1: Atom";
    char rook_name[] = "Drawing 2: Rook";

    Mat atom_image = Mat::zeros(w, w, CV_8UC3);
    Mat rook_image = Mat::zeros(w, w, CV_8UC3);

    // atom image drawing
    Test_Ellipse(atom_image, 0);
    Test_Ellipse(atom_image, 45);
    Test_Ellipse(atom_image, 90);
    Test_Ellipse(atom_image, 135);

    Test_FilledCircle(atom_image, Point(w/2, w/2));

    // rook image drawing
    Test_Polygon( rook_image );

    rectangle(rook_image,
            Point(0, 7*w/8),
            Point(w, w),
            Scalar(0, 255, 255),
            -1,
            8);

    Test_Line(rook_image, Point(0, 15*w/16), Point(w, 15*w/16));
    Test_Line(rook_image, Point(w/4, 7*w/8), Point(w/4, w));
    Test_Line(rook_image, Point(w/2, 7*w/8), Point(w/2, w));
    Test_Line(rook_image, Point(3*w/4, 7*w/8), Point(3*w/4, w));

    namedWindow(atom_name, 1);
    imshow(atom_name, atom_image);
    moveWindow(atom_name, 0, 200);
    namedWindow(rook_name, 1);
    imshow(rook_name, rook_image);
    moveWindow(rook_name, w, 200);

    waitKey(0);

    return 0;
}

void Test_Ellipse(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;

    ellipse(img, Point(w/2, w/2), Size(w/4, w/16), angle, 0, 360, Scalar(255, 0, 0), thickness, lineType);
}

void Test_FilledCircle(Mat img, Point center)
{
    int thickness = -1;
    int lineType = 8;

    circle(img, center, w/32, Scalar(0, 0, 255), thickness, lineType);
}

void Test_Polygon(Mat img)
{
    int lineType = 8;
    Point rook_points[1][20];  
    rook_points[0][0]  = Point(    w/4,   7*w/8 );
    rook_points[0][1]  = Point(  3*w/4,   7*w/8 );
    rook_points[0][2]  = Point(  3*w/4,  13*w/16 );
    rook_points[0][3]  = Point( 11*w/16, 13*w/16 );
    rook_points[0][4]  = Point( 19*w/32,  3*w/8 );
    rook_points[0][5]  = Point(  3*w/4,   3*w/8 );
    rook_points[0][6]  = Point(  3*w/4,     w/8 );
    rook_points[0][7]  = Point( 26*w/40,    w/8 );
    rook_points[0][8]  = Point( 26*w/40,    w/4 );
    rook_points[0][9]  = Point( 22*w/40,    w/4 );
    rook_points[0][10] = Point( 22*w/40,    w/8 );
    rook_points[0][11] = Point( 18*w/40,    w/8 );
    rook_points[0][12] = Point( 18*w/40,    w/4 );
    rook_points[0][13] = Point( 14*w/40,    w/4 );
    rook_points[0][14] = Point( 14*w/40,    w/8 );
    rook_points[0][15] = Point(    w/4,     w/8 );
    rook_points[0][16] = Point(    w/4,   3*w/8 );
    rook_points[0][17] = Point( 13*w/32,  3*w/8 );
    rook_points[0][18] = Point(  5*w/16, 13*w/16 );
    rook_points[0][19] = Point(    w/4,  13*w/16 );

    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 20 };

    fillPoly( img,
    ppt,
    npt,
    1,
    Scalar( 255, 255, 255 ),
    lineType );
}

void Test_Line(Mat img, Point start, Point end)
{
    int thickness = 2;
    int lineType = 8;

    line(img,
        start,
        end,
        Scalar(0, 0, 0),
        thickness,
        lineType);
}

/********************************** END **********************************************/

