/*
 **************************************************************************************
 *       Filename:  main.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-26 14:33:15
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include "opencv2/core/core.hpp"  
#include <iostream>  
#include <stdio.h>
  
using namespace std;  
using namespace cv;  
  
static void help()  
{  
    cout  
        << "\n--------------------------------------------------------------------------" << endl  
        << "This program shows how to create matrices(cv::Mat) in OpenCV and its serial"  
        << " out capabilities"                                                            << endl  
        << "That is, cv::Mat M(...); M.create and cout << M. "                            << endl  
        << "Shows how output can be formated to OpenCV, python, numpy, csv and C styles." << endl  
        << "Usage:"                                                                       << endl  
        << "./cvout_sample"                                                               << endl  
        << "--------------------------------------------------------------------------"   << endl  
        << endl;  
}  
  
int main(int argc, char* argv[])  
{  
    help();  
    Mat M(2,2, CV_8UC3, Scalar(0,0,255));  
    cout << "M = " << endl << " " << M << endl << endl;  
    // 对于二维多通道图像，首先要定义其尺寸，即行数和列数。  
    // 然后，需要指定存储元素的数据类型以及每个矩阵点的通道数  
    // Scalar（0,0,255）表示输入的像素值  
  
    M.create(4,4, CV_8UC(2));  
    cout << "M = "<< endl << " "  << M << endl << endl;  
    // 这个创建方法不能为矩阵设初值，它只是在改变尺寸时重新为矩阵数据开辟内存。  
  
    int sz[3] = {2,2,2};  
    Mat L(3,sz, CV_8UC(1), Scalar::all(0));  
    // 如何创建一个超过两维的矩阵：指定维数，然后传递一个指向一个数组的指针，这个数组包含每个维度的尺寸；其余的        // 相同  
  
    Mat E = Mat::eye(4, 4, CV_64F);  
    cout << "E = " << endl << " " << E << endl << endl;  
  
    Mat O = Mat::ones(2, 2, CV_32F);  
    cout << "O = " << endl << " " << O << endl << endl;  
  
    Mat Z = Mat::zeros(3,3, CV_8UC1);  
    cout << "Z = " << endl << " " << Z << endl << endl;  
    // MATLAB形式的初始化方式： zeros(), ones(), :eyes()   
  
    Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);  
    cout << "C = " << endl << " " << C << endl << endl;  
    //  对于小矩阵你可以用逗号分隔的初始化函数:  
  
    Mat RowClone = C.row(1).clone();  
    cout << "RowClone = " << endl << " " << RowClone << endl << endl;  
    // 使用 clone() 或者 copyTo() 为一个存在的 Mat 对象创建一个新的信息头。  
  
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
  
    //OpenCV支持使用运算符<<来打印其它常用OpenCV数据结构   
    Point2f P(5, 1);  
    cout << "Point (2D) = " << P << endl << endl;  
    //2维点  
  
    Point3f P3f(2, 6, 7);  
    cout << "Point (3D) = " << P3f << endl << endl;  
    //3维点  
  
    vector<float> v;  
    v.push_back( (float)CV_PI);   v.push_back(2);    v.push_back(3.01f);  
    cout << "Vector of floats via Mat = " << Mat(v) << endl << endl;  
    //基于cv::Mat的std::vector  
  
    vector<Point2f> vPoints(20);  
    for (size_t i = 0; i < vPoints.size(); ++i)  
        vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));  
    cout << "A vector of 2D Points = " << vPoints << endl << endl;  
    //std::vector点  
  
    char ch;  
    while(ch!='c')  
    {  
        ch=getchar();  
    }  
    //输入字符c退出程序  
    return 0;  
} 

/********************************** END **********************************************/
