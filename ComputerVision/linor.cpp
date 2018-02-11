#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\stitching.hpp>
#include <vector>
#include <iostream>

int RECT_X = 844;
int RECT_Y = 477;

using namespace std;
using namespace cv;

cv::Mat pixelToTransparency(cv::Mat input, int r, int g, int b);

Rect rect(Point(0, 0), Point(RECT_X, RECT_Y));
Rect rect1(Point(0, 0), Point(RECT_X*0.7, RECT_Y));
Rect rect2(Point(0, 0), Point(RECT_X, RECT_Y));
Rect rect3(Point(RECT_X*0.3, 0), Point(RECT_X, RECT_Y));

int main()
{
	VideoCapture video("input/winter.mp4"); // video source

	if (!video.isOpened())
	{
		puts("***Could not initialize capturing...***\n");
		return 1;
	}
	int size = (int)video.get(CAP_PROP_FRAME_COUNT);

	Mat frame, copy_frame;
	vector<Mat> leftFrames, rightFrames;

	for (int i = 0; i < size; i++)
	{
		video >> frame;
		copy_frame = frame.clone();

		frame = frame(rect);
		frame = frame(rect1);
		if (i % 40 == 0)
			leftFrames.push_back(frame);

		copy_frame = copy_frame(rect2);
		copy_frame = copy_frame(rect3);
		if (i % 40 == 0)
			rightFrames.push_back(copy_frame);

		char c = (char)waitKey(int(video.get(CV_CAP_PROP_FPS)));
		if (c == 27)
			break;
	}

	destroyAllWindows();
	frame.release();

	Mat leftEyeResult, rightEyeResult, theFrames;

	hconcat(leftEyeResult, theFrames);
	imwrite("output/linor/theFramesL.jpg", theFrames);
	Stitcher s1 = Stitcher::createDefault();
	s1.stitch(leftFrames, leftEyeResult);
	imwrite("output/linor/leftEyeResult.jpg", leftEyeResult);
	cv::Mat leftEye = leftEyeResult; // load as color image BGR
	imwrite("output/linor/Left Eye After Transparency.png", pixelToTransparency(leftEye, 0, 0, 0)); // save as .png file (which supports alpha channels/transparency)

	hconcat(rightEyeResult, theFrames);
	imwrite("output/linor/theFramesR.jpg", theFrames);
	Stitcher s2 = Stitcher::createDefault();
	s2.stitch(rightFrames, rightEyeResult);
	imwrite("output/linor/rightEyeResult.jpg", rightEyeResult);
	cv::Mat rightEye = rightEyeResult; // load as color image BGR
	imwrite("output/linor/Right Eye After Transparency.png", pixelToTransparency(rightEye, 0, 0, 0)); // save as .png file (which supports alpha channels/transparency)
}

cv::Mat pixelToTransparency(cv::Mat input, int r, int g, int b)
{
	cv::Mat input_bgra2;
	cv::cvtColor(input, input_bgra2, CV_BGR2BGRA);
	for (int y = 0; y < input_bgra2.rows; ++y)
		for (int x = 0; x < input_bgra2.cols; ++x)
		{
			cv::Vec4b & pixel = input_bgra2.at<cv::Vec4b>(y, x);
			if (pixel[0] == r && pixel[1] == g && pixel[2] == b)
				pixel[3] = 0;
		}
	return input_bgra2;
}