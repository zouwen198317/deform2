
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include <iostream>
using namespace std;

#include "tool.h"

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

	// arm and binary
	Mat bone_binary = imread("data/arm.png", 0);
	for (int i = 0; i< src.rows; i++)
	{
		for (int j = 0; j< src.cols; j++)
		{
			if (bone_binary.at<uchar>(i, j) != 0)
			{
				bone_binary.at<uchar>(i, j) = 255;
			}
		}
	}
	Mat bone = Mat(src.size(), CV_8UC3);
	for (int i = 0; i< src.rows; i++)
	{
		for (int j = 0; j< src.cols; j++)
		{
			if (bone_binary.at<uchar>(i, j) == 255)
			{
				bone.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
			}
		}
	}

	// show
	imshow("src", src);
	imshow("src_binary", src_binary);
	imshow("bone", bone);
	imshow("bone_binary", bone_binary);
	waitKey();

	Mat other = Mat(src.size(), CV_8UC3, Scalar::all(0));
	Mat other_binary = Mat(src.size(), CV_8UC1, Scalar::all(0));
	for (int i = 0; i< src.rows; i++)
	{
		for (int j = 0; j< src.cols; j++)
		{
			if (bone_binary.at<uchar>(i, j) == 0
				&&src_binary.at<uchar>(i, j) == 255)
			{
				other.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
				other_binary.at<uchar>(i, j) = 255;
			}
		}
	}
	// show
	imshow("other", other);
	imshow("other_binary", other_binary);
	imwrite("other_binary.png", other_binary);
	waitKey();

	Mat newbackground = imread("data/background.png");
	imshow("re", newbackground);
	waitKey();

	Mat bone2 = imread("data/arm2.png");
	
	// smoooth
	Mat bone2_smooth = imread("data/arm2.png", 0);
	for (int i = 0; i< src.rows; i++)
	{
		for (int j = 0; j< src.cols; j++)
		{
			if (bone2_smooth.at<uchar>(i, j) != 0)
			{
				bone2_smooth.at<uchar>(i, j) = 255;
			}
		}
	}
	GaussianBlur( bone2_smooth, bone2_smooth, Size( 3, 3 ), 0, 0 );
	imshow("blur", bone2_smooth);
	waitKey();

	for (int i = 0; i< 1; i++)
	{
		 bone2 = getDecline(bone2);
	}

	// Mat bone2 = getDecline(getDecline(imread("data/arm2.png")));
	for (int i = 0; i< src.rows; i++)
	{
		for (int j = 0; j< src.cols; j++)
		{
			
			if (bone2.at<Vec3b>(i, j) != Vec3b(0, 0, 0))
			{
				newbackground.at<Vec3b>(i, j) = bone2.at<Vec3b>(i, j);
			}
			
			/*
			float ratio = 1.0*bone2_smooth.at<uchar>(i, j)/255;

			for (int k = 0; k< 3; k++)
			{
				newbackground.at<Vec3b>(i, j)[k] = ratio*bone2.at<Vec3b>(i, j)[k]+(1-ratio)*newbackground.at<Vec3b>(i, j)[k];
			}
			*/
		}
	}

	imshow("re", newbackground);
	waitKey();

	other_binary = imread("other_binary.png", 0);
	for (int i = 0; i< src.rows; i++)
	{
		for (int j = 0; j< src.cols; j++)
		{
			int tmp = other_binary.at<uchar>(i, j);
			// std::cout<<tmp<<std::endl;
			if (tmp !=  0)
			{
				newbackground.at<Vec3b>(i, j) = other.at<Vec3b>(i, j);
			}
		}
	}


	imshow("re", newbackground);
	waitKey();

	imwrite("result.png", newbackground);

	return 0;


}