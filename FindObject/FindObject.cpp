// FindObject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include <opencv.hpp>

using namespace cv;
using namespace std;


int main()
{
	Mat srcMat = imread("E:\\课程\\大二下\\数字图像处理\\topic1.jpg");
	Mat hsv, gray, bin1, bin2, bin;
	resize(srcMat, srcMat, Size(400, 400));
	cvtColor(srcMat, hsv, CV_BGR2HSV);
	Mat Result;
	srcMat.copyTo(Result);
	int minH = 0;
	int maxH = 20;
	int minS = 43;
	int maxS = 255;
	int minV = 55;
	int maxV = 255;

	inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), bin1);
	minH = 160;
	maxH = 180;
	inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), bin2);

	bitwise_or(bin1, bin2, bin);

	vector<vector<Point>> contours;
	findContours(bin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	Point2f vtx[4];
	for (int i = 0; i < contours.size(); i++) {
		/*drawContours(img, contours, i, Scalar(255, 0, 0), 3, 8);*/

		RotatedRect rbox = minAreaRect(contours[i]);
		rbox.points(vtx);
		float width = rbox.size.width;
		float height = rbox.size.height;
		float prop = width / height;
		float area = width * height;
		if (area > 1000)
		{
			for (int j = 0; j < 4; j++)
			{
				line(Result, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 255, 255), 2, CV_AA);
			}
		}
	}
	imshow("srcMat", srcMat);
	imshow("result", Result);
	waitKey(0);
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
