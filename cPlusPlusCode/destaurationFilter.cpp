#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(){

    //Read image
    Mat image = imread("../assets/putin.jpg");
    
    //convert to hsv color space
    Mat hsvImage, hsvImageCopy;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    //create a clone of the hsv image to work on
    hsvImageCopy = hsvImage.clone();

    //convert to float32
    hsvImageCopy.convertTo(hsvImageCopy, CV_32F);

    //split the channels
    vector<Mat> channels;
    split(hsvImageCopy, channels);

    //Define desturation scale
    float saturationScale = 0.01;

    //Desaturation. Multiply S channel desaturation scale value
    channels[1] = channels[1] * saturationScale;

    //Limiting pixel values between 0 and 255
    min(channels[1], 255, channels[1]);
    max(channels[1], 0, channels[1]);

    //merge the channels
    merge(channels, hsvImageCopy);

    //Covert back from float32
    hsvImageCopy.convertTo(hsvImageCopy, CV_8UC3);

    //Convert back to BGR color space
    Mat saturatedImage;
    cvtColor(hsvImageCopy, saturatedImage, COLOR_HSV2BGR);

    //create windows to display image
    namedWindow("image", WINDOW_NORMAL);
    namedWindow("hsvImage", WINDOW_NORMAL);
    namedWindow("saturated", WINDOW_NORMAL);

    //display images
    imshow("image", image);
    imshow("hsvImage", hsvImage);
    imshow("saturated", saturatedImage);

    //Press Esc to exit the program
    waitKey(0);

    //close all the opened windows
    destroyAllWindows();

    return 0;
}