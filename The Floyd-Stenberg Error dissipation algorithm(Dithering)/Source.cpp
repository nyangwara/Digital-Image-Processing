#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdlib.h>
uchar saturated_add(uchar val1, schar val2)
{
    int16_t val1_int = val1;
    int16_t val2_int = val2;
    int16_t tmp = val1_int + val2_int;

    if (tmp > 255)
    {
        return 255;
    }
    else if (tmp < 0)
    {
        return 0;
    }
    else
    {
        return tmp;
    }
}

int main() {
    cv::Mat src = imread("LABS/Peppers.png", cv::IMREAD_ANYDEPTH);
    cv::Mat res = src.clone();
    int quantError;
    float diff1, diff2, diff3, diff4;
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            if (res.at<uchar>(y, x)>128) {
                quantError = res.at<uchar>(y, x)-255;
                res.at<uchar>(y, x) = 255;
            }
            else 
            {
                quantError = res.at<uchar>(y, x) - 0;
                res.at<uchar>(y, x) = 0;
            }
            diff1 = (quantError * 7.0) / 16.0;
            diff2 = (quantError * 1.0) / 16.0;
            diff3 = (quantError * 5.0) / 16.0;
            diff4 = (quantError * 3.0) / 16.0;
            if ((x != (src.cols - 1)) && (y != 0) && (y != (src.rows - 1)))
            {
                res.at<uchar>(x + 0, y + 1) = saturated_add(res.at<uchar>(x + 0, y + 1), diff1);
                res.at<uchar>(x + 1, y + 1) = saturated_add(res.at<uchar>(x + 1, y + 1), diff2);
                res.at<uchar>(x + 1, y + 0) = saturated_add(res.at<uchar>(x + 1, y + 0), diff3);
                res.at<uchar>(x + 1, y - 1) = saturated_add(res.at<uchar>(x + 1, y - 1), diff4);
            }
        }
    }

    imshow("Input_Image", src);
    imshow("Dithered Image", res);
    cv::waitKey(0);
}