#include <iostream>
#include <algorithm>
#include <direct.h>
#include <Windows.h>
#include<fstream>
#include <sys/stat.h>
//#include <unistd.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
string win_src = "src";
// Function declaration
bool CheckExistenceOfFolder(const std::string folder_name);
bool MakingFolder(const std::string folder_name);
bool OutputTxTResult(char* str);
void FilteringCircles(int num_circles, cv::Mat& img);
void show(string window_name, cv::Mat img);
// Global vasiables' declaration
int img_cnt = 0;
string filename_png_i[100];
string filename_jpg_i[100];
string filename_jpeg_i[100];
string filename_i[100];
string file_name;
string output_img[100];
int result_x[100];
int result_y[100];
int result_radius[100];

int main()
{
	// Set the input image
	cin >> file_name;

	// Creates a folder for outputting results
	if (!CheckExistenceOfFolder("output"))
	{
		if (!MakingFolder("output"))
		{
			return(1);
		}
	}

	// Converts the image to grayscale
	cv::Mat grayMat;
	cv::Mat img;

	string tmp_img = file_name;
	img = cv::imread(tmp_img);
	cvtColor(img, grayMat, cv::COLOR_BGR2GRAY);

	// Smoooth the grayscale image
	cv::Mat smoothMat;
	cv::medianBlur(grayMat, smoothMat, 7);
	//cv::bilateralFilter(grayMat, smoothMat, 7, 79,79);
	// Edge detection : Canny 
	cv::Mat cannyMat;
	cv::Canny(smoothMat, cannyMat, 80, 230);

	// Thresholding
	cv::Mat binImage;
	cv::threshold(cannyMat, binImage, 128, 255, cv::THRESH_BINARY);

	// Hough transformaition
	vector<cv::Vec3f> circles;
	cv::HoughCircles(binImage, circles, cv::HOUGH_GRADIENT, 2, binImage.rows / 6, 200, 100);
	char result[100];
	sprintf_s(result, "===========================\n");
	OutputTxTResult(result);
	sprintf_s(result, "%s\n", file_name.c_str());
	OutputTxTResult(result);
	for (int i = 0; i < circles.size(); i++)
	{
		cv::Vec3i c = circles[i];
		cv::Point center = cv::Point(c[0], c[1]);
		int radius = c[2];
		// Gets the center and radius of the circles.
		result_x[i] = c[0];
		result_y[i] = c[1];
		result_radius[i] = c[2];
	}
	FilteringCircles(circles.size(), img);

	return 0;
}
// *** Checking the exising of the folder.
bool CheckExistenceOfFolder(const std::string folder_name)
{
	struct stat statBuf;

	if (stat(folder_name.c_str(), &statBuf) != 0)
	{
		return false;
	}
	return true;
}
// ***  making the folder if it doesn't exist.
bool MakingFolder(const std::string folder_name)
{
	if (_mkdir(folder_name.c_str()) != 0)
	{
		return false;
	}
	return true;	
}

// *** Outputing results to a txt file.
bool OutputTxTResult(char* str)
{
	FILE* fp;
	errno_t error;
	error = fopen_s( &fp,"Output.txt", "a");
	if (error != 0)
	{
		cout << "Fails to open Output.txt. Try again." << endl;
		return false;
	}
	else
	{
		fprintf(fp, "%s", str);
	}
	fclose(fp);
	return true;
}
// *** Filtering out wrong circles
void FilteringCircles( int num_circles, cv::Mat& img)
{
	int remove_cnt = 0;
	// Estimates the average of all circles.
	int ave = 0;
	int sum = 0;
	for (int i = 0; i < num_circles; i++)
	{
		sum += result_radius[i];
	}
	ave = sum / num_circles;

	// Removes too big and/or small circles
	int min = ave * 0.4;
	int max = ave * 1.3;
	char result[100];
	for (int i = 0; i < num_circles; i++)
	{
		if ( min < result_radius[i]  && result_radius[i] < max )
		{
			cv::Point center = cv::Point(result_x[i], result_y[i]);
			circle(img, center, result_radius[i], cv::Scalar(0, 0, 255), 3);
			circle(img, center, 5, cv::Scalar(0, 255, 0), -1);
			sprintf_s(result, "   x = % d  y = % d  radius = % d\n", result_x[i], result_y[i], result_radius[i]);
			OutputTxTResult(result);
		}
		else
		{
			remove_cnt++;
		}
	}
	sprintf_s(result, "Number of coins : %d\n", num_circles - remove_cnt);
	OutputTxTResult(result);
	string output_img = "output\\" + file_name;
	cv::imwrite(output_img, img);
	show(file_name, img);
}
void show(string window_name, cv::Mat img)
{
	cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
	cv::moveWindow(window_name, 700, 150);
	cv::imshow(window_name, img);
	cv::waitKey(0);
};