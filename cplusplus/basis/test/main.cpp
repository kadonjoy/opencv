/*
 **************************************************************************************
 *       Filename:  main.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-02-09 17:38:34
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
    const char* path = "../744x992_dst.jpg";
    Mat img = imread(path);
    if (!img.data){
        cout << "Wrong Image" << endl;
        return -1;
    }

    Mat kern = getStructuringElement(MORPH_RECT, Size(5, 5));

    Mat erosion_img, dilate_img;
    //腐蚀
    erode(img, erosion_img, kern);
    //膨胀
    dilate(img, dilate_img, kern);

    imshow("original image", img);
    imshow("erosion image", erosion_img);
    imshow("dilate image", dilate_img);


    Mat open_mat, close_mat, gradient_mat, tophat_mat, blackhat_mat;
    morphologyEx(img, open_mat, MORPH_OPEN, kern);
    morphologyEx(img, close_mat, MORPH_CLOSE, kern);
    morphologyEx(img, gradient_mat, MORPH_GRADIENT, kern);
    morphologyEx(img, tophat_mat, MORPH_TOPHAT, kern);
    morphologyEx(img, blackhat_mat, MORPH_BLACKHAT, kern);

    imshow("Opening", open_mat);
    imshow("Closing", close_mat);
    imshow("Grandient", gradient_mat);
    imshow("Tohat", tophat_mat);
    imshow("Black", blackhat_mat);

    cvWaitKey(0);
    return 0;
}



/********************************** END **********************************************/

