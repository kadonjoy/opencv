/*
 **************************************************************************************
 *       Filename:  main.cpp
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-20 13:58:45
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */
#include <stdio.h>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <string>
//#include <iostream>

using namespace std;

double** createGaussianTemplate(int iSize, double sigma)
{
    double **guass;
    double sum = 0;
    double x2 = 0;
    double y2 = 0;
    int center = (iSize - 1) / 2;
    guass = new double*[iSize];//注意，double*[k]表示一个有10个元素的指针数组

    for (int i = 0; i < iSize; ++i) {
        guass[i] = new double[iSize];
    }
    for (int i = 0; i < iSize; i++) {//使用x2，y2降低了运算速度，提高了程序的效率
        x2 = pow(double(i - center), 2);
        for (int j = 0; j<iSize; j++) {
            y2 = pow(double(j - center), 2);
            sum += guass[i][j] = exp(-(x2 + y2) / (2 * sigma*sigma));
        }
    }
    if (sum != 0) {
        //归一化  
        for (int i = 0; i<iSize; i++) {
            for (int j = 0; j<iSize; j++) {
                guass[i][j] /= sum;
            }
        }
    }

    return guass;
}

double* CreateMuban(int iSize ,double sigma)
{
    double *gauss = new double[iSize];//声明一维模板
    int radius = (iSize - 1) / 2;//这是高斯半径
    double MySigma = 2 * sigma * sigma;
    double value = 0;
    for (int i = 0; i < iSize; i++) {//高斯函数前面的常数项因为在归一化的时候将会消去，故这里不重复计算
        gauss[i] = exp(-(i - radius)*(i - radius)/MySigma);
        value = value + gauss[i];
    }
    for (int i = 0; i < iSize; i++) {//归一化
        gauss[i] = gauss[i] / value;
    }

    return gauss;
}

bool JudgeEdge(int i, int max, int radius)
{
    if ((i - radius) < 0 || (i + radius) >= max)
        return true;
    return false;
}

IplImage*  operatorImage(IplImage* img, double* Muban, int iSize)
{
    //创建一张新的图片来进行滤波操作
    IplImage* NewImage = cvCreateImage(cvSize(img->width, img->height), 8, 3);
    int radius = (iSize - 1) / 2;
    int r = 0;
    int g = 0;
    int b = 0;
    CvScalar cs;
    //复制图片
    cvCopy(img, NewImage);
    //先对I，也就是垂直方向进行操作
    for (int j = 0; j < NewImage->width; ++j) {
        for (int i = 0; i < NewImage->height; ++i) {
            //先判断是否是边缘,不是则操作，是则跳过不处理，保持原样
            if (!JudgeEdge(i, NewImage->height, radius)) {
                for (int k = 0; k < iSize; ++k) {
//                    printf("i: %d, radius: %d, k: %d, j: %d", i, radius, k, j);
                    cs = cvGet2D(NewImage, i - radius + k, j);   //获取像素  
                    b = b + (int)((double)cs.val[0] * Muban[k]);
                    g = g + (int)((double)cs.val[1] * Muban[k]);
                    r = r + (int)((double)cs.val[2] * Muban[k]);
                }
                cs = cvGet2D(NewImage, i, j);
                cs.val[0] = b;
                cs.val[1] = g;
                cs.val[2] = r;
                cvSet2D(NewImage, i, j, cs);
                b = 0;
                g = 0;
                r = 0;
            }
        }
    }
    //在对J，也就是水平方向进行操作
    for (int i = 0; i < NewImage->height; ++i) {
        for (int j = 0; j < NewImage->width; ++j) {
            //先判断是否是边缘,不是则操作，是则跳过不处理，保持原样
            if (!JudgeEdge(j, NewImage->width, radius)) {
                for (int k = 0; k < iSize; ++k) {
                    cs = cvGet2D(NewImage, i, j - radius + k);   //获取像素  
                    b = b + (int)((double)cs.val[0] * Muban[k]);
                    g = g + (int)((double)cs.val[1] * Muban[k]);
                    r = r + (int)((double)cs.val[2] * Muban[k]);
                }
                cs = cvGet2D(NewImage, i, j);
                cs.val[0] = b;
                cs.val[1] = g;
                cs.val[2] = r;
//                printf("r: %d, g: %d, b: %d", r, g, b);
                cvSet2D(NewImage, i, j, cs);
                b = 0;
                g = 0;
                r = 0;
            }
        }
    }

    if(Muban != NULL) {
        delete Muban;
    }
    
    return NewImage;
}
int main(int argc, char** argv)
{
    int size = 3;
#if 0
    double **gaussianTemplate = createGaussianTemplate(size, 1);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf(" %f \t", gaussianTemplate[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < size; i++) {
        delete gaussianTemplate[i];
    }
#endif
    IplImage* srcImg = cvLoadImage("../../images/2976x3968.jpg");
    IplImage* tmpImg = cvCreateImage(cvSize(500,500),8,3);
//    IplImage* dstImg = cvCreateImage(cvSize(tmpImg->width, tmpImg->height),8,3);

    cvResize(srcImg, tmpImg);
    IplImage* dstImg = operatorImage(tmpImg, CreateMuban(3, 1.0), size);


    cvNamedWindow("src");
    cvNamedWindow("Gaussian Filter");
    cvShowImage("src", tmpImg);
    cvShowImage("Gaussian Filter", dstImg);
    cvWaitKey(50000);

    cvReleaseImage(&srcImg);
    cvReleaseImage(&tmpImg);
    cvDestroyAllWindows();

    return 0;
}

/********************************** END **********************************************/

