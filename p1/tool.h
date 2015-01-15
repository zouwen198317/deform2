
#ifndef TOOL_H_
#define TOOL_H_

#include <stdlib.h>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

// √∞≈›≈≈–Ú
void BubbleSort(float* data, int n)  
{  
	float tmp;  
	for (int i = 1; i < n; i++)  
	{  
		for (int j = n - 1; j >= i; j--)  
		{  
			if (data[j] < data[j - 1])  
			{  
				tmp = data[j - 1];  
				data[j - 1] = data[j];  
				data[j] = tmp;  
			}  
		}  
	}  
}

// œ˚≥˝Õ‚Œß“ª»¶œÒÀÿ
Mat getDecline(Mat a)
{
	assert (a.type() == CV_8UC3);

	for (int i = 0; i< a.rows; i++)
	{
		for (int j = 0; j< a.cols-1; j++)
		{
			if (a.at<Vec3b>(i, j) != Vec3b(0, 0, 0) && a.at<Vec3b>(i, j+1) == Vec3b(0, 0, 0))
			{
				a.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}

	for (int i = 0; i< a.rows; i++)
	{
		for (int j = a.cols-1; j> 0; j--)
		{
			if (a.at<Vec3b>(i, j) != Vec3b(0, 0, 0) && a.at<Vec3b>(i, j-1) == Vec3b(0, 0, 0))
			{
				a.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}

	return a;
}

#endif
