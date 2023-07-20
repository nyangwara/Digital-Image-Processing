#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    cv::Mat foreground, background, alpha, res,ref_vert,ref_horz,transposition;

    // reading input images

    foreground = cv::imread("LABS/barbara.png", cv::IMREAD_ANYDEPTH);

    if (foreground.empty()) { cout << "Ошибка загрузка изображение foreground" << endl; return EXIT_FAILURE; }

    background = cv::imread("LABS/boat.png", cv::IMREAD_ANYDEPTH);

    if (background.empty()) { cout << "Ошибка загрузка изображение background" << endl; return EXIT_FAILURE; }

    alpha = cv::imread("LABS/Peppers.png", cv::IMREAD_ANYDEPTH);

    if (alpha.empty()) { cout << "Ошибка загрузка изображение alpha channel image" << endl; return EXIT_FAILURE; }

    // check size and data type of input images

    // size should be the same and data type should be 1 channel 8 bpp

    if (foreground.dims != 2 || background.dims != 2 || alpha.dims != 2 || \

        1 != foreground.elemSize() || 1 != background.elemSize() || 1 != alpha.elemSize() || \

        foreground.cols != background.cols || foreground.cols != alpha.cols || \

        foreground.rows != background.rows || foreground.rows != alpha.rows) {

        cout << "Inconsistent input data!" << endl; return EXIT_FAILURE;

    }

    // memory allocation for output image

    res = cv::Mat::zeros(alpha.rows, alpha.cols, CV_8UC1);

    // alpha blending
    for (int row = 0; row < alpha.rows; row++)

    {

        for (int col = 0; col < alpha.cols; col++)

        {

            res.at<uchar>(row, col) = (uchar)((float)foreground.at<uchar>(row, col) * ((float)alpha.at<uchar>(row, col) / 255.f)

                + (float)background.at<uchar>(row, col) * (1.f - (float)alpha.at<uchar>(row, col) / 255.f));
        }

    }
    //TRANSPOSITION
    // memory allocation for image transposition
    transposition= cv::Mat::zeros(foreground.rows, foreground.cols, CV_8UC1);
    for (int row = 0; row < foreground.rows; row++)
    {
        int new_row = foreground.rows - 1-row;
        for (int col = 0; col < foreground.cols; col++)
        {
            int new_col = foreground.cols - 1 - col;
            transposition.at<uchar>(row, col) = (uchar)foreground.at<uchar>(new_row, new_col);
        }

    }
    //HORIZONTAL_AXIS
    // memory allocation for image reflection_along_horizontal_axis
    ref_horz = cv::Mat::zeros(foreground.rows, foreground.cols, CV_8UC1);
    for (int row = 0; row < foreground.rows; row++)
    {
        for (int col = 0; col < foreground.cols; col++)
        {
            int new_col = foreground.rows - 1 - col;
            ref_horz.at<uchar>(row, col) = (uchar)foreground.at<uchar>(row, new_col);
        }

    }
    //VERTICAL_AXIS
    // memory allocation for image reflection_along_vertical axis
    ref_vert = cv::Mat::zeros(foreground.rows, foreground.cols, CV_8UC1);
    for (int row = 0; row < foreground.rows; row++)
    {
        int new_row = foreground.rows - 1 - row;
        for (int col = 0; col < foreground.cols; col++)
        {
            ref_vert.at<uchar>(row, col) = (uchar)foreground.at<uchar>(new_row, col);
        }

    }

    // write result
    cv::imwrite("original.png", foreground);
    cv::imwrite("Transposed.png", transposition);
    cv::imwrite("horizontal.png", ref_horz);
    cv::imwrite("Vertical.png", ref_vert);
    //display res
    cv::imshow("original.png", foreground);
    /*cv::imshow("Transposed.png", transposition);*/
    cv::imshow("horizontal.png", ref_horz);
    cv::imshow("Vertical.png", ref_vert);
    cv::waitKey(0);
    return 0;

}





