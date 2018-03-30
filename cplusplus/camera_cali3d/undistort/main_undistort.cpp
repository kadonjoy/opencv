/*
 **************************************************************************************
 *       Filename:  main_undistort.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-30 11:08:08
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */
#include <opencv2/opencv.hpp>  
#include <opencv2/calib3d/calib3d.hpp>  
using namespace std;  
using namespace cv;  
  
/** 
 * @主函数 
 */  
int main( int argc, char** argv )  
{  
  
    /// 读取一副图片，不改变图片本身的颜色类型（该读取方式为DOS运行模式）  
        Mat src = imread( argv[1], 1 );  
        Mat distortion = src.clone();  
        Mat camera_matrix = Mat(3, 3, CV_32FC1);  
        Mat distortion_coefficients;  
  
  
        //导入相机内参和畸变系数矩阵  
        FileStorage file_storage("out_camera_data.xml", FileStorage::READ);  
        file_storage["Camera_Matrix"] >> camera_matrix;  
        file_storage["Distortion_Coefficients"] >> distortion_coefficients;  
        file_storage.release();  
  
        //矫正  
        undistort(src, distortion, camera_matrix, distortion_coefficients);  
  
        imshow("img", src);  
        imshow("undistort", distortion);  
        imwrite("undistort.jpg", distortion);  
  
        waitKey(0);  
        return 0;  
}

/********************************** END **********************************************/

