/*
 **************************************************************************************
 *       Filename:  main_dft.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-27 14:15:17
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include"opencv2/core/core.hpp"  
#include"opencv2/imgproc/imgproc.hpp"  
#include"opencv2/highgui/highgui.hpp"  
   
#include<iostream>  
   
using namespace cv;  
using namespace std;  
   
static void help()  
{  
        cout << endl  
               <<  "This program demonstrated the use ofthe discrete Fourier transform (DFT). " << endl  
               <<  "The dft of an image is taken and it'spower spectrum is displayed."         << endl  
               <<  "Usage:"                                                                     << endl  
               <<  " [image_name -- default lena.jpg]"                       <<endl << endl;  
}  
   
int main(int argc,char ** argv)  
{  
        help();  
   
        const char* filename =  "1.jpg";  
   
        Mat I = imread(filename,CV_LOAD_IMAGE_GRAYSCALE);  
        if( I.empty())  
               return -1;  
   
        Mat padded;                            //expand inputimage to optimal size  
        int m = getOptimalDFTSize( I.rows );  
        int n = getOptimalDFTSize( I.cols ); //on the border add zero values  
        copyMakeBorder(I, padded, 0, m - I.rows,0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));  
   
        Mat planes[] ={Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};  
        Mat complexI;  
        merge(planes, 2, complexI);         // Add to the expanded another planewith zeros  
   
        dft(complexI, complexI);            // this way the result may fit inthe source matrix  
   
        // compute the magnitude and switch tologarithmic scale  
        // => log(1 + sqrt(Re(DFT(I))^2 +Im(DFT(I))^2))  
        split(complexI, planes);                   // planes[0] = Re(DFT(I),planes[1] = Im(DFT(I))  
        magnitude(planes[0], planes[1], planes[0]);//planes[0] = magnitude  
        Mat magI = planes[0];  
   
        magI += Scalar::all(1);                    // switch to logarithmicscale  
        log(magI, magI);  
   
        // crop the spectrum, if it has an oddnumber of rows or columns  
        magI = magI(Rect(0, 0, magI.cols & -2,magI.rows & -2));  
   
        // rearrange the quadrants of Fourierimage  so that the origin is at the imagecenter  
        int cx = magI.cols/2;  
        int cy = magI.rows/2;  
   
        Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant  
        Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right  
        Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left  
        Mat q3(magI, Rect(cx, cy, cx, cy)); //Bottom-Right  
   
        Mat tmp;                           // swap quadrants(Top-Left with Bottom-Right)  
        q0.copyTo(tmp);  
        q3.copyTo(q0);  
        tmp.copyTo(q3);  
   
        q1.copyTo(tmp);                    // swap quadrant (Top-Rightwith Bottom-Left)  
        q2.copyTo(q1);  
        tmp.copyTo(q2);  
   
        normalize(magI, magI, 0, 1, CV_MINMAX);// Transform the matrix with float values into a  
        // viewable image form (float betweenvalues 0 and 1).  
   
        imshow("Input Image"       , I  );    // Show the result  
        imshow("spectrum magnitude", magI);  
        moveWindow("spectrum magnitude", I.rows, 0);
        waitKey();  
   
        return 0;  
} 



/********************************** END **********************************************/

