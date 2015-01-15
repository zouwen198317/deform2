
#include "interface.h"

int main()
{
	// 3 points
	Point shoulder = cvPoint(245-1, 224-1);
	Point middle = cvPoint(230-1, 364-1);
	Point wrist = cvPoint(188-1, 517-1);

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
	Mat bone = Mat(src.size(), CV_8UC3, Scalar::all(0));
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

	transArm2(src, src_binary, bone, bone_binary, shoulder, middle, wrist, -15, -15);



	return 0;
}