#include <opencv2\highgui.hpp>

using namespace cv;

class MouseCropper
{
 
private:
    static bool currentlySelecting;
    static Rect selection;
    static Point topLeft;
    static int tracking;
    static void showImage();
    
public:
    static void mouseCrop(int event, int x, int y, int, void*);
    static Rect getSelectionRect();
    static bool isSelecting();
    static Mat image;
};

