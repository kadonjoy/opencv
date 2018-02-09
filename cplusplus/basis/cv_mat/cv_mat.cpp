/*
 **************************************************************************************
 *       Filename:  cv_mat.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-02-08 17:30:08
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat M(2,2, CV_8UC3, Scalar(0, 0, 255));
    cout << "M=" << endl << " " << M << endl;
//    imwrite("dst.jpg", M);
    M.create(5,5, CV_8UC(2));
    cout << "M=" << endl << " " << M << endl;

    int sz[3] = {2,2,2};  
    Mat L(3,sz, CV_8UC(1), Scalar::all(0));  
//    cout << "L=" << endl << " " << L <<endl;

    Mat E = Mat::eye(5, 5, CV_64F);  
    cout << "E = " << endl << " " << E << endl << endl;  
          
    Mat O = Mat::ones(2, 2, CV_32F);  
    cout << "O = " << endl << " " << O << endl << endl;  
                  
    Mat Z = Mat::zeros(3,3, CV_8UC1);  
    cout << "Z = " << endl << " " << Z << endl << endl;  
    // MATLAB形式的初始化方式： zeros(), ones(), :eyes()  

    Mat R = Mat(3, 2, CV_8UC3);  
    randu(R, Scalar::all(0), Scalar::all(255));  
    //randu：为矩阵随机分配像素值，分配数字的范围为0-255；  
  
    cout << "R (default) = " << endl <<        R           << endl << endl;  
    //默认输出  
    cout << "R (python)  = " << endl << format(R,"python") << endl << endl;  
    //python输出  
    cout << "R (numpy)   = " << endl << format(R,"numpy" ) << endl << endl;  
    //numpy输出  
    cout << "R (csv)     = " << endl << format(R,"csv"   ) << endl << endl;  
    //以逗号分隔的数值 (CSV)  
    cout << "R (c)       = " << endl << format(R,"C"     ) << endl << endl;  
    //以C输出

    return 0;
}

/********************************** END **********************************************/

