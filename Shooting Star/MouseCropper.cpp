#include "MouseCropper.h"
#include <opencv2\imgproc.hpp>

bool MouseCropper::currentlySelecting = false;
Rect MouseCropper::selection;
Point MouseCropper::topLeft;
Mat MouseCropper::image;

void MouseCropper::mouseCrop(int event, int x, int y, int, void*)
{
    if (currentlySelecting)
    {
        selection.x = MIN(x, topLeft.x);
        selection.y = MIN(y, topLeft.y);
        selection.width = std::abs(x - topLeft.x);
        selection.height = std::abs(y - topLeft.y);

        selection &= Rect(0, 0, image.cols, image.rows);
    }
    if (event == EVENT_LBUTTONDOWN)
    {
        topLeft = Point(x, y);
        selection = Rect(x, y, 0, 0);
        currentlySelecting = true;
    }
    else if (event == EVENT_LBUTTONUP)
    {
        currentlySelecting = false;
        showImage();
    }
}

Rect MouseCropper::getSelectionRect()
{
    return selection;
}
bool MouseCropper::isSelecting()
{
    return currentlySelecting;
}

void MouseCropper::showImage()
{
    Rect bound = MouseCropper::getSelectionRect();

    Mat result;
    Mat bgModel, fgModel;

    grabCut(image, result, bound, bgModel, fgModel, 1, GC_INIT_WITH_RECT);

    compare(result, GC_PR_FGD, result, CMP_EQ);
    Mat foreground(image.size(), CV_8UC3, Scalar(0, 255, 0));
    image.copyTo(foreground, result);

    rectangle(image, bound, Scalar(255, 255, 255), 1);

    imshow("Foreground", foreground);
}