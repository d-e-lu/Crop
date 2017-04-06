#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <sstream>
#include <iostream>


/* CORE FUNCTIONALITY (CORE MODULE) */

using namespace cv;

/* MAT */
/*
	Header - size of matrix, method of storing, address, etc.

	Matrix - matrix
		   - Useful constructors:
		   - Mat::Mat(int rows, int cols, int type)
		   - Mat::Mat(int rows, int cols, int type, const Scalar& s)
*/

void matReference() {

	/* Assignment */
	Mat A, C; // Creates just header parts
	A = imread("fileName", IMREAD_COLOR);
	Mat B(A); // Copy constructor -> only copies header
	C = A; // Assignment operator -> only copies header
	/* Result -> A, B, C are different headers, but all point to same matrix*/


	/* Copy */
	Mat F = A.clone(); // Copies matrix
	Mat G;
	A.copyTo(G); // Copies matrix
	/* Result -> F and G are separate from A and can be modified without affecting each other*/


	/* Creation */
	Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255)); // Creates matrix of size 2 x 2 of type 8 bit unsigned char with 3 channels
	/* Result -> M = [0, 0, 255, 0, 0, 255;
					  0, 0, 255, 0, 0, 255]*/
	M.create(4, 4, CV_8UC3); // Creates 4x4 matrix of same type, but cannot specify values

	Mat E = Mat::eye(4, 4, CV_64F); // Creates an identity matrix
	Mat O = Mat::ones(2, 2, CV_32F); // Creates a matrix of ones
	Mat Z = Mat::zeros(3, 3, CV_8UC1); // Creates a matrix of zeros

	Mat Q = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0); // For small matrices you can assign values themselves
	Mat RowClone = Q.row(1).clone(); // Create a clone of the second row of the matrix

	Mat R = Mat(3, 2, CV_8UC3);
	randu(R, Scalar::all(0), Scalar::all(255)); // Creates a random matrix
}

/* Colour reduction */
/*
	-Used to reduce the amount of colours in an image, making it easier to work with
	-Unsigned char values 0-255, we reduce this value to the lowest multiple of 10
	-4->0, 13->10, 75->70...
	-We do this with the equation I_new = (I_old/10) * 10
	-Because multiplication and division is expensive we create a lookup table instead
*/

uchar* calculateLookupTable(std::string* argv)
{
	// Creates a lookup table for the matrix to use
	int divideWith = 0;
	std::stringstream s;
	s << argv[2];
	s >> divideWith;
	if (!s || !divideWith)
	{
		std::cout << "Invalid number entered for dividing." << std::endl;
		return nullptr;
	}
	uchar table[256];
	for (int i = 0; i < 256; ++i)
	{
		table[i] = (uchar)(divideWith * i / divideWith);
	}
	return table;
}

Mat& scanImageAndReduceC(Mat& I, const uchar* const table)
{
	// Efficient way to reduce image
	int channels = I.channels();
	int nRows = I.rows;
	int nCols = I.cols * channels;

	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i)
	{
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]];
		}
	}
	return I;
}

void generalLookupTable(uchar* table, Mat& I)
{
	// For replacing values in an image to some other values
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i)
	{
		p[i] = table[i];
	}

	Mat J; // Output image

	LUT(I, lookUpTable, J); // Look up table
}

/* Mask operations */
/*
	-TLDR: Convolution
	-Requires imgproc.hpp
*/
#include <opencv2\imgproc.hpp>
void sharpen(const Mat& image, Mat& result)
{
	
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
									  -1, 5, -1,
									  0, -1, 0);
	filter2D(image, result, image.depth(), kernel);
}


/* Common Image Operations */

void fileIO()
{
	//Works with bmp, JPEG, png, and others

	Mat img = imread("Path/To/File"); // 3 channel BRG image

	Mat grayImg = imread("Path/To/File", 0); // grayscale image

	imwrite("Path/To/File", img); //save image
}

void intensity(Mat& img)
{
	// Get intensity of pixels
	int x = 0, y = 0;

	Scalar intensity1 = img.at<uchar>(y, x);
	Scalar intensity2 = img.at<uchar>(Point(x, y)); // Same thing

	Vec3b intensity = img.at<Vec3b>(y, x);
	uchar blue = intensity.val[0];
	uchar green = intensity.val[1];
	uchar red = intensity.val[2];

	// Set intensity of pixels
	img.at<uchar>(y, x) = 128;
}

void primitiveOperations(Mat& img) 
{
	img = Scalar(0); //Sets grayscale image to black

	Rect r(10, 10, 100, 100);
	Mat smallImg = img(r); // Get region of interest

	// Change colour image to grayscale
	Mat colourImg = imread("image.jpg");
	Mat grey;
	cvtColor(img, grey, COLOR_BGR2GRAY);

	//Change image type
	Mat dst;
	img.convertTo(dst, CV_32F);
}

void viewImage()
{
	Mat img = imread("image.jpg");

	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", img);
	waitKey();
}

/* Random generator */
void random()
{
	RNG rng(0xFFFFFFFF);
	Mat matrix;


	Scalar meanVal(0.5);
	Scalar stdDev(1);
	rng.fill(matrix, RNG::NORMAL, meanVal, stdDev);

	float x = rng.next();
}