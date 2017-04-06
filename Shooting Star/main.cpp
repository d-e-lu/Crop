#include <opencv2\highgui\highgui.hpp>
#include <opencv2\objdetect.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\video.hpp>
#include "MouseCropper.h"

#include <iostream>

using namespace cv; 
using namespace std;

static const string winName = "Detector";

int main(int argc, char** argv) 
{
    Mat src;
    namedWindow(winName);
    setMouseCallback(winName, MouseCropper::mouseCrop);
    while (true)
    {
        
        src = imread("C:\\Users\\Dylan\\Desktop\\bunny.jpg");
        src.copyTo(MouseCropper::image);
        Rect selection = MouseCropper::getSelectionRect();
        if (MouseCropper::isSelecting() && selection.width > 0 && selection.height > 0)
        {
            Mat roi(src, selection);
            bitwise_not(roi, roi);
        }

        imshow(winName, src);
        waitKey(1);
    }


	return 0;
}

