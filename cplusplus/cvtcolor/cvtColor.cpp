/*
 **************************************************************************************
 *       Filename:  cvtColor.cpp
 *    Description:  demo for opencv cvtColor function
 *
 *        Version:  1.0
 *        Created:  2017-08-31 10:03:39
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */
#include <errno.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>   
#include <iostream>   
#include <opencv/cv.h>
#include <opencv/highgui.h>
   

using namespace std;
using namespace cv;

void cvtGray(Mat & input_image);
void cvtRGB2YV12(Mat & input_image);

// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:  main function
// =====================================================================================
int main ( int argc, char *argv[] )
{
	Mat image;  
	cout << "\nProgram " << argv[0] << endl << endl;

	if ( argc != 2 ) {
	    cout << "please input image name...\n" << endl;
	    return -1;
	}

	image = imread(argv[1]);
	if (!image.data) {
	    printf("No image data\n");
	    return -1;
	}

        cvtGray(image);
        cvtRGB2YV12(image);

	/*-----------------------------------------------------------------------------
	 *  create one window that called by test_cv
	 *-----------------------------------------------------------------------------*/
/* 	namedWindow("test_cv", WINDOW_NORMAL);
 * 	imshow("test_cv", image);
 *     cout << "key value: " << waitKey(0) << endl;
 */

	return EXIT_SUCCESS;
}		// ----------  end of function main  ---------- 


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cvtGray
 *  Description:  cvt one rgb image to gray image, and then show it
 * =====================================================================================
 */
void cvtGray ( Mat & input_image )
{
    Mat imageGary;
    cvtColor(input_image, imageGary, CV_RGB2GRAY);
    namedWindow("test_cv_gray", WINDOW_NORMAL);
    imshow("test_cv_gray", imageGary);
    cout << "key value: " << waitKey(0) << endl;
    return ;
}/* -----  end of function cvtGray  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cvtRGB2YV12
 *  Description:  covert an rgb image to yuv12 format
 * =====================================================================================
 */
void cvtRGB2YV12 ( Mat & input_image )
{
    FILE *yuv_file;										/* output-file pointer */
    const char * yuv_file_file_name = "test.yuv";		/* output-file name    */
    Mat imageGary;

    cvtColor(input_image, imageGary, CV_RGB2YUV_I420);
    yuv_file	= fopen( yuv_file_file_name, "w" );
    if ( yuv_file == NULL ) {
        fprintf ( stderr, "couldn't open file '%s'; %s\n", yuv_file_file_name, strerror(errno) );
        exit (EXIT_FAILURE);
    }
    // width and height needs to be changed by user
    fwrite(imageGary.data, 1, 1920 * 1080 * 1.5, yuv_file);

    if( fclose(yuv_file) == EOF ) {			/* close output file   */
        fprintf ( stderr, "couldn't close file '%s'; %s\n",
                yuv_file_file_name, strerror(errno) );
        exit (EXIT_FAILURE);
    }

    return ;
}/* -----  end of function cvtRGB2YV12  ----- */
/********************************** END **********************************************/

