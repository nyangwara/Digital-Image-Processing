#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;
using namespace cv;

//the pixel lying outside the image i.e. (x – j, y – k) are reflected back into the image
int reflect(int M, int x)
{
    if (x < 0)
    {
        return -x - 1;
    }
    if (x >= M)
    {
        return 2 * M - x - 1;
    }
    return x;
}

int circular(int M, int x)
{
    if (x < 0)
        return x + M;
    if (x >= M)
        return x - M;
    return x;
}


void noBorderProcessing(Mat src, Mat res, float Kernel[][3])
{

    float sum;
    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
            sum = 0.0;
            for (int k = -1; k <= 1; k++) {
                for (int j = -1; j <= 1; j++) {
                    sum = sum + Kernel[j + 1][k + 1] * src.at<uchar>(y - j, x - k);
                }
            }
            res.at<uchar>(y, x) = sum;
        }
    }
}

void refletedIndexing(Mat src, Mat res, float Kernel[][3])
{
    float sum, x1, y1;
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            sum = 0.0;
            for (int k = -1; k <= 1; k++) {
                for (int j = -1; j <= 1; j++) {
                    x1 = reflect(src.cols, x - j);
                    y1 = reflect(src.rows, y - k);
                    sum = sum + Kernel[j + 1][k + 1] * src.at<uchar>(y1, x1);
                }
            }
            res.at<uchar>(y, x) = sum;
        }
    }
}
//coordinates that exceed the bounds of the image wrap around to the opposite side
void circularIndexing(Mat src, Mat res, float Kernel[][3])
{
    float sum, x1, y1;
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            sum = 0.0;
            for (int k = -1; k <= 1; k++) {
                for (int j = -1; j <= 1; j++) {
                    x1 = circular(src.cols, x - j);
                    y1 = circular(src.rows, y - k);
                    sum = sum + Kernel[j + 1][k + 1] * src.at<uchar>(y1, x1);
                }
            }
            res.at<uchar>(y, x) = sum;
        }
    }
}

int main()
{

    Mat src, res,dst;


    /// Load an image
    //src = cv::imread("Images4DZ/Gray_Win.bmp", cv::IMREAD_ANYDEPTH);
    src = cv::imread("LABS/baboon.png", cv::IMREAD_ANYDEPTH);
    //low pass filtering
    float Kernel[3][3] = {
                        {1 / 9.0, 1 / 9.0, 1 / 9.0},
                          {1 / 9.0, 1 / 9.0, 1 / 9.0},
                          {1 / 9.0, 1 / 9.0, 1 / 9.0}
    };

    res = src.clone();
    for (int y = 0; y < src.rows; y++)
        for (int x = 0; x < src.cols; x++)
            res.at<uchar>(y, x) = 0.0;

    circularIndexing(src, res, Kernel);
    //Unsharpen Masking 
    dst = cv::Mat::zeros(res.rows, res.cols, CV_8UC1);
    float k = 0.7;
    for (int y = 0; y < res.rows; y++) {
        for (int x = 0; x < res.cols; x++) {
            dst.at<uchar>(y, x) = src.at<uchar>(y,x) + (uchar)(k * (float)(src.at<uchar>(y, x) - res.at<uchar>(y, x)));
        }
    }
    imshow("Source Image", src);
    imshow("Low Pass Filter", res);
    imshow("Unsharpen Masking", dst);
    waitKey();


    return 0;
}