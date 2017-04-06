#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

void smoothImage(const Mat& src)
{
	int kernelWidth = 5, kernelHeight = 5;

	// Normalized Box filter
	Mat blurFiltered;
	blur(src, blurFiltered, Size(kernelWidth, kernelHeight));
	// Also can do
	Mat boxFiltered;
	bool isNormalized = true;
	boxFilter(src, boxFiltered, -1, Size(kernelWidth, kernelHeight), Point(-1,-1), isNormalized);

	// Gaussian Filter
	Mat gaussFiltered;
	double sigmaX = 0;
	GaussianBlur(src, gaussFiltered, Size(kernelWidth, kernelHeight), sigmaX);
}

void erodeAndDilate(const Mat& image, const Mat& kernel)
{
	/* Erosion */
	// Computes local minimum over area of kernel
	// Image becomes darker and brighter areas become thinner
	Mat erodedImage;
	erode(image, erodedImage, kernel);

	/* Dilation */
	// Computes local maximum over area of kernel
	// Image becomes brighter and brighter areas become thicker
	Mat dilatedImage;
	dilate(image, dilatedImage, kernel);
}