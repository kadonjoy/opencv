/*
 **************************************************************************************
 *       Filename:  main_contrast.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-27 10:02:59
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    double alpha;
    int beta;
    double t;

    Mat image = imread("1.jpg");
    Mat image_dst = Mat::zeros(image.size(), image.type());
    Mat image_dst1 = Mat::zeros(image.size(), image.type());
    Mat image_dst2 = Mat::zeros(image.size(), image.type());

    cout << " Basic Linear Transforms " << endl;  
    cout << "-------------------------" << endl;  
    cout << "* Enter the alpha value [1.0-3.0]: ";  
    cin >> alpha;  
    cout << "* Enter the beta value [0-100]: ";  
    cin >> beta;

    // .at+[] method
    t = (double)getTickCount();

    // 执行运算 new_image(i,j) = alpha*image(i,j) + beta
    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {
            for (int channel = 0; channel < 3; channel++) {
                image_dst.at<Vec3b>(x,y)[channel] = saturate_cast<uchar>(alpha * image.at<Vec3b>(x,y)[channel] + beta);
            }
        }
    }

    cout << ".at+[] times passed in miscellaneous: " << 1000*(getTickCount() - t)/getTickFrequency() << endl;

    // .ptr+[] method
    t = (double)getTickCount();

    int nr = image.rows;
    int nc = image.cols * image.channels(); // total number of elements per line

    for (int x = 0; x < nr; x++) {
        uchar *src_ptr = image.ptr<uchar>(x);
        uchar *dst_ptr = image_dst1.ptr<uchar>(x);
        for (int y = 0; y < nc; y++) {
            dst_ptr[y] = saturate_cast<uchar>(alpha * src_ptr[y] + beta);
        }
    }

    cout << ".ptr+[] times passed in miscellaneous: " << 1000*(getTickCount() - t)/getTickFrequency() << endl;

    // convertTo method
    t = (double)getTickCount();
    image.convertTo(image_dst2, -1, alpha, beta);
    cout << "convertTo times passed in miscellaneous: " << 1000*(getTickCount() - t)/getTickFrequency() << endl;

    namedWindow("src pic", 1);
    namedWindow("dst pic", 1);
    namedWindow("dst1 pic", 1);
    namedWindow("dst2 pic", 1);

    imshow("src pic", image);
    imshow("dst pic", image_dst);
    imshow("dst1 pic", image_dst1);
    imshow("dst2 pic", image_dst2);

    waitKey(0);

    return 0;
}

/********************************** END **********************************************/

