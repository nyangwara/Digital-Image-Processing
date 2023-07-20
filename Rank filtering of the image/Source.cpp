#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdlib.h>
using namespace std;
using namespace cv;

Mat adaptive_threshold(Mat src)
{
	Mat result(src.size(), src.type());
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			int sum = 0, avg = 0, t = 7;
			for (int m = i - 1; m <= i + 1; m++)
			{
				for (int n = j - 1; n <= j + 1; n++)
				{
					if (m < 0 || n < 0 || m > src.rows - 1 || n > src.cols - 1)
					{
						t--;
						continue;
					}
					sum += src.at<uchar>(m, n);
				}
			}
			avg = sum / t;
			if (src.at<uchar>(i, j) > avg)
				result.at<uchar>(i, j) = 255;
			else
				result.at<uchar>(i, j) = 0;
		}
	}
	return result;
}

int main()
{
	Mat src, binary;
	src = imread("LABS/blood.jpg", IMREAD_GRAYSCALE);
	binary = src.clone();
	binary = adaptive_threshold(src);
	cv::imshow("Original", src);
	cv::imshow("Binary", binary);
	waitKey(0);
	return 0;
}