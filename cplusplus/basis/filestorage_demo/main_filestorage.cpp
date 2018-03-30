/*
 **************************************************************************************
 *       Filename:  main_filestorage.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-29 09:29:36
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <opencv2/core/core.hpp>
#include <iostream>
#include <time.h>

using namespace std;
using namespace cv;

void writeFileContext(FileStorage& fs, const string& filename);
void dumpFileContext(FileStorage& fs, const string& filename);

int main(int argc, char** argv)
{
    string filename = "test.xml";

/*     FileStorage fs(filename, FileStorage::WRITE);
 *     writeFileContext(fs, filename);
 *     fs.release();
 */
    FileStorage fs(filename, FileStorage::READ);
    dumpFileContext(fs, filename);
    fs.release();

    return 0;
}

void writeFileContext(FileStorage& fs, const string& filename)
{
    int width = 1280;
    int height = 720;

    fs << "width" << width;
    fs << "height" << height;

    Mat m1 = Mat::eye(3,3,CV_8U);
    Mat m2 = Mat::ones(3,3,CV_8U);
    Mat m3 = (m1+1).mul(m2);
    fs << "resultMatrix" << m3;

    Mat cameraMatrix = (Mat_<double>(3,3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
    Mat distCoeffs = (Mat_<double>(5,1) << 0.1, 0.01, -0.001, 0, 0);
    fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;

    time_t curTime;
    time(&curTime);
    fs << "calibrationDate" << asctime(localtime(&curTime));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dumpFileContext
 *  Description:  
 * =====================================================================================
 */
    void
dumpFileContext ( FileStorage& fs, const string& filename )
{
    int width;
    int height;
    fs["width"] >> width;
    fs["height"] >> height;
    cout << "width =" << width << endl;
    cout << "height =" << height << endl << endl;

    Mat resultMatrix;
    fs["resultMatrix"] >> resultMatrix;
    cout    << "resultMatrix = " << endl << resultMatrix << endl << endl;

    Mat cameraMatrix;
    fs["cameraMatrix"] >> cameraMatrix;
    cout    << "cameraMatrix = " << endl << cameraMatrix << endl << endl;

    Mat distCoeffs;
    fs["distCoeffs"] >> distCoeffs;
    cout    << "distCoeffs = " << endl << distCoeffs << endl << endl;

    string calibrationDate;
    fs["calibrationDate"] >> calibrationDate;
    cout    << "calibrationDate: " << calibrationDate << endl;
    
    return ;
}		/* -----  end of function dumpFileContext  ----- */

/********************************** END **********************************************/
