#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main() {

    string path = "BMP/RGB_Win.bmp";
    Mat img = imread(path);
    Mat imgGray,imgResize,imgBlur,unsharpMask, lowConstrastMask;
    double sigma = 5, threshold = 5, amount = 1;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    resize(imgGray,imgResize, Size(), 2, 2);

    //unsharp mask implementation-unsharpened image=original image +amount*(original-blurred)
    GaussianBlur(imgResize, imgBlur, Size(7, 7), sigma, 0);//create a blurred version 

    lowConstrastMask = abs(imgResize - imgBlur) < threshold;
    unsharpMask = imgResize * (1 + amount) + imgBlur * (-amount);
    


    imshow("Image", img);
    //imshow("Gray_Image",imgGray);
    imshow("Resized_Gray_Image",imgResize);
    imshow("Gaussian_Blur", imgBlur);
    imshow("LowContrast_Mask", lowConstrastMask);
    imshow("Unsharpened_image_Mask", unsharpMask);
    waitKey(0);
    return 0;
}