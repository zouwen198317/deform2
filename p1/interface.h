
#include "mls/imgwarp_mls.h"
#include "mls/imgwarp_mls_rigid.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

vector<cv::Point2i> getVcvPoint(Point a, Point b, Point c)
{
	vector<cv::Point2i> vL;
		vL.push_back(cv::Point2i(a.x, a.y));
		vL.push_back(cv::Point2i(b.x, b.y));
		vL.push_back(cv::Point2i(c.x, c.y));
	return vL;
}

Mat transUpArm(Mat src, Mat src_binary, Mat bone, Mat bone_binary, Point &begin, Point &middle, Point &end, float angle)
{
	assert(src.channels() == 3 && bone.channels() == 3
		&& src_binary.channels() == 1 && bone_binary.channels() == 1);

	angle = angle/360*3.1416;

	// 换算为左下角零点
	//	从0， 0开始
	int height = src.cols;

	float bx = begin.x;
	float by = height-1 - begin.y;

	float ex = end.x;
	float ey = height-1 - end.y;

	float mx = middle.x;
	float my = height-1 - middle.y;

	// 逆时针
	// angle为角度数
	Vec2f newVector = Vec2f(mx - bx, my - by);
	newVector = Vec2f(newVector[0]*cos(angle)-newVector[1]*sin(angle), newVector[0]*sin(angle)+newVector[1]*cos(angle));
	newVector = Vec2f(newVector[0]+bx, newVector[1]+by);
	Point newmiddle = cvPoint(newVector[0], height-1-newVector[1]);

	// 逆时针
	// angle为角度数
	Vec2f newVec2 = Vec2f(ex-bx, ey-by);
	newVec2 = Vec2f(newVec2[0]*cos(angle)-newVec2[1]*sin(angle), newVec2[0]*sin(angle)+newVec2[1]*cos(angle));
	newVec2 = Vec2f(newVec2[0]+bx, newVec2[1]+by);
	Point newend = cvPoint(newVec2[0], height-1-newVec2[1]);

	ImgWarp_MLS *imgTrans;
	imgTrans = new ImgWarp_MLS_Rigid();
	imgTrans->alpha = 1.0;
	imgTrans->gridSize = 5;
	Mat re = imgTrans->setAllAndGenerate
		(
		bone,
		getVcvPoint(begin, middle, end),
		getVcvPoint(begin, newmiddle, newend),
		src.cols,
		src.rows,
		1.0);

	// imshow("sc", bone);
	// imshow("re", re);
	// waitKey();

	middle = newmiddle;
	end = newend;

	return re;
}

Mat transDownArm(Mat src, Mat src_binary, Mat bone, Mat bone_binary, Point &begin, Point &middle, Point &end, float angle)
{
	assert(src.channels() == 3 && bone.channels() == 3
		&& src_binary.channels() == 1 && bone_binary.channels() == 1);

	angle = angle/360*3.1416;

	// 换算为左下角零点
	//	从0， 0开始
	int height = src.cols;

	float bx = begin.x;
	float by = height-1 - begin.y;

	float ex = end.x;
	float ey = height-1 - end.y;

	float mx = middle.x;
	float my = height-1 - middle.y;

	Vec2f newPoint = Vec2f(ex-mx, ey-my);
	// 逆时针
	// angle为角度数
	newPoint = Vec2f(newPoint[0]*cos(angle)-newPoint[1]*sin(angle), newPoint[0]*sin(angle)+newPoint[1]*cos(angle));
	newPoint = Vec2f(newPoint[0]+mx, newPoint[1]+my);
	Point newend = cvPoint(newPoint[0], height-1-newPoint[1]);

	ImgWarp_MLS *imgTrans;
	imgTrans = new ImgWarp_MLS_Rigid();
	imgTrans->alpha = 1.0;
	imgTrans->gridSize = 5;
	Mat re = imgTrans->setAllAndGenerate
		(
		bone,
		getVcvPoint(begin, middle, end),
		getVcvPoint(begin, middle, newend),
		src.cols,
		src.rows,
		1.0);

	// imshow("sc", bone);
	// imshow("re", re);
	// waitKey();
	// middle = newmiddle;
	end = newend;

	return re;
}

void transArm1(Mat src, Mat src_binary, Mat bone, Mat bone_binary, Point begin, Point middle, Point end, float angle, float angle2)
{
	assert(src.channels() == 3 && bone.channels() == 3
		&& src_binary.channels() == 1 && bone_binary.channels() == 1);

	Mat a = transUpArm(src, src_binary, bone, bone_binary, begin, middle, end, angle);
	Mat b = transDownArm(src, src_binary, a, bone_binary, begin, middle, end, angle);

	imshow("a", a);
	imshow("b", b);
	waitKey();
}

void transArm2(Mat src, Mat src_binary, Mat bone, Mat bone_binary, Point begin, Point middle, Point end, float angle, float angle2)
{
	assert(src.channels() == 3 && bone.channels() == 3
		&& src_binary.channels() == 1 && bone_binary.channels() == 1);

	angle = angle/360*3.1416;
	angle2 = angle2/360*3.1416;

	// 换算为左下角零点
	//	从0， 0开始
	int height = src.cols;

	float bx = begin.x;
	float by = height-1 - begin.y;

	float ex = end.x;
	float ey = height-1 - end.y;

	float mx = middle.x;
	float my = height-1 - middle.y;

	// 逆时针
	// angle为角度数
	Vec2f newVec = Vec2f(mx-bx, my-by);
	newVec = Vec2f(newVec[0]*cos(angle)-newVec[1]*sin(angle), newVec[0]*sin(angle)+newVec[1]*cos(angle));
	newVec = Vec2f(newVec[0]+bx, newVec[1]+by);
	Point newmiddle = cvPoint(newVec[0], height-1-newVec[1]);

	// 逆时针
	// angle为角度数
	Vec2f newVec2 = Vec2f(ex-bx, ey-by);
	newVec2 = Vec2f(newVec2[0]*cos(angle)-newVec2[1]*sin(angle), newVec2[0]*sin(angle)+newVec2[1]*cos(angle));
	newVec2 = Vec2f(newVec2[0]+bx, newVec2[1]+by);
	Point newend = cvPoint(newVec2[0], height-1-newVec2[1]);

	ex = newend.x;
	ey = height-1 - newend.y;

	mx = newmiddle.x;
	my = height-1 - newmiddle.y;

	Vec2f newVec3 = Vec2f(ex-mx, ey-my);
	// 逆时针
	// angle为角度数
	newVec3 = Vec2f(newVec3[0]*cos(angle2)-newVec3[1]*sin(angle2), newVec3[0]*sin(angle2)+newVec3[1]*cos(angle2));
	newVec3 = Vec2f(newVec3[0]+mx, newVec3[1]+my);
	Point newend2 = cvPoint(newVec3[0], height-1-newVec3[1]);

	ImgWarp_MLS *imgTrans;
	imgTrans = new ImgWarp_MLS_Rigid();
	imgTrans->alpha = 1.0;
	imgTrans->gridSize = 5;
	Mat re = imgTrans->setAllAndGenerate
		(
		bone,
		getVcvPoint(begin, middle, end),
		getVcvPoint(begin, newmiddle, newend2),
		src.cols,
		src.rows,
		1.0);

	imshow("sc", bone);
	imshow("re", re);
	waitKey();

	imwrite("arm2.png", re);

	// return re;
}

/*
bool DeformWin::calcWarpedImg(){
	if (ui->viewPointEdit->srcPointPaint.getPointList().length() !=
		ui->viewPointEdit->dstPointPaint.getPointList().length()){
			curImg = oriImg;
			return false;
	}

	ImgWarp_MLS *imgTrans;
	if (ui->cmbDeformAlg->currentText()==QString("MLS Similarity")){
		imgTrans = new ImgWarp_MLS_Similarity();
		imgTrans->alpha = ui->spinAlpha->value();
		imgTrans->gridSize = ui->SldGrid->value();
	}
	else if (ui->cmbDeformAlg->currentText()==QString("MLS Rigid")){
		imgTrans = new ImgWarp_MLS_Rigid();
		imgTrans->alpha = ui->spinAlpha->value();
		imgTrans->gridSize = ui->SldGrid->value();
	}
	else if (ui->cmbDeformAlg->currentText()==QString("Piecewise Affine")){
		imgTrans = new ImgWarp_PieceWiseAffine();
		imgTrans->alpha = ui->spinAlpha->value();
		imgTrans->gridSize = ui->SldGrid->value();
		((ImgWarp_PieceWiseAffine *)imgTrans)->backGroundFillAlg = ImgWarp_PieceWiseAffine::BGMLS;
		//         imgTrans = new ImgTrans_MLS_Affine();
		//         imgTrans->alpha = ui->spinAlpha->value();
		//         imgTrans->gridSize = ui->SldGrid->value();
	}
	else {
		//         imgTrans = new ImgTrans_MLS_Affine();
		//         imgTrans->alpha = ui->spinAlpha->value();
		//         imgTrans->gridSize = ui->SldGrid->value();
	}

	//imgTrans->setTargetSize(oriImg.cols, oriImg.rows);
	//imgTrans->setSize(oriImg.cols, oriImg.rows);
	//imgTrans->setSrcPoints(getVcvPoint(ui->viewPointEdit->srcPointPaint.getPointList()));
	//imgTrans->setDstPoints(getVcvPoint(ui->viewPointEdit->dstPointPaint.getPointList()));
	////    imgTrans->alpha = 1;
	////    imgTrans->gridSize = 10;

	//imgTrans->calcDelta();
	//curImg = imgTrans->genNewImg(oriImg, 1);
	curImg = imgTrans->setAllAndGenerate(
		oriImg,
		getVcvPoint(ui->viewPointEdit->srcPointPaint.getPointList()),
		getVcvPoint(ui->viewPointEdit->dstPointPaint.getPointList()),
		oriImg.cols, oriImg.rows, 1);
	delete imgTrans;
	return true;
}
*/