
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;  

#include <iostream>  
using namespace std;  

#include <stdlib.h>
#include <stdio.h>

#include "pcl.h"

//间隔多少像素进行采样  
static int add_pixels = 5;  

// 得到contour
void getContour(Mat src, Mat &dst, Mat &field, Mat &test)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours( src.clone(), contours, hierarchy, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_NONE );

	dst = Mat::zeros(src.size(), CV_8UC3);
	drawContours( dst, contours, 0, cvScalar(255, 255, 255), 1, 8, hierarchy, 0, Point() );

	field = Mat::zeros(src.size(), CV_8UC3);
	drawContours( field, contours, 0, cvScalar(255, 255, 255), -1, 8, hierarchy, 0, Point() );

	test = Mat::zeros(src.size(), CV_8UC3);
	vector<vector<Point> > contours2;
	vector<Point>contours3;
	for (int i = 0; i< contours[0].size(); i++)
	{
		if (contours[0][i].x % add_pixels == 0
			||contours[0][i].y % add_pixels == 0)
		{
			contours3.push_back(contours[0][i]);
		}
		
	}

	Mat sasd = Mat::zeros(src.size(), CV_8UC3);
	for (int i = 0; i< contours3.size(); i++)
	{
		circle(sasd, contours3[i], 1, cvScalar(255, 255, 255), 1, 8, 0);
		imshow("as", sasd);
		// waitKey(1);
	}


	contours2.push_back(contours3);
	drawContours( test, contours2, 0, cvScalar(255, 255, 255), 1, 8, hierarchy, 0, Point() );
	imshow("test", test);
	waitKey();

	imshow("src", src);
	imshow("contour", dst);
	imshow("field", field);
	waitKey();
}

bool pointIn(int i, int j, int (*a)[2])
{
	if (a[i][0] == -1)
	{
		return false;
	}

	else if (j < a[i][0])
	{
		return false;
	}
	else if (j > a[i][1])
	{
		return false;
	}
	return true;
}

void getObj(Mat pic_binary, char *name)  
{  
	Mat countour, field, test;
	getContour(pic_binary, countour, field, test);

	Mat allpoints = Mat::zeros(countour.size(), CV_8UC3);
	for (int i = 0; i< allpoints.rows; i+= add_pixels)
	{
		for (int j=  0; j< allpoints.cols; j+= add_pixels)
		{
			allpoints.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
		}
	}

	for (int i = 0; i< allpoints.rows; i+= add_pixels)
	{
		for (int j=  0; j< allpoints.cols; j+= add_pixels)
		{
			if (field.at<Vec3b>(i, j) == Vec3b(0, 0, 0))
			{
				allpoints.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}
	imshow("ponts", allpoints);
	waitKey();

	for (int i = 0; i< allpoints.rows-add_pixels; i+= add_pixels)
	{
		for (int j=  0; j< allpoints.cols-add_pixels; j+= add_pixels)
		{
			if (allpoints.at<Vec3b>(i, j) == Vec3b(255, 255, 255)
				&&allpoints.at<Vec3b>(i+add_pixels, j+add_pixels) == Vec3b(255, 255, 255)
				&&allpoints.at<Vec3b>(i, j+add_pixels) == Vec3b(255, 255, 255))
			{
				allpoints.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}

	Mat allcontour = allpoints.clone();
	for (int i = 0; i< allpoints.rows; i+= 1)
	{
		for (int j=  0; j< allpoints.cols; j+= 1)
		{
			if (countour.at<Vec3b>(i, j) == Vec3b(255, 255, 255))
			{
				if (i%5== 0
					|| j%5 == 0)
				{
					allcontour.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
				}
				
			}
		}
	}
	imshow("contours", allcontour);
	waitKey();
}  

int main()
{
	// src and binary
	Mat src = imread("data/1.jpg");
	Mat src_binary = imread("data/1.png", 0);
	for (int i = 0; i< src.rows; i++)
	{
		for (int j = 0; j< src.cols; j++)
		{
			if (src_binary.at<uchar>(i, j) != 0)
			{
				src_binary.at<uchar>(i, j) = 255;
			}
		}
	}

	getObj(src_binary, "");

	testPcl();

	return 0;
}