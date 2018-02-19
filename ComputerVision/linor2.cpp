#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{
	clock_t startTime, endTime;
	startTime = clock();

	// Source video
	string filename = "input/winter.mp4";
	VideoCapture video(filename);

	if (!video.isOpened())
	{
		cout << "Error when reading the video file..";
		return 1;
	}

	vector<Mat> leftArr, rightArr;
	Mat tempFrame;
	Mat leftPano;
	Mat rightPano;

	const int NUM_OF_FRAMES = 20;
	const double STRIP_WIDTH = 0.6; // Percent

	int frameCount = video.get(CV_CAP_PROP_FRAME_COUNT);
	int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = video.get(CV_CAP_PROP_FRAME_HEIGHT) - 1;

	Rect rectLeft(Point(0, 0), Point(width * STRIP_WIDTH, height));
	Rect rectRight(Point(width * (1 - STRIP_WIDTH), 0), Point(width, height));

	for (int i = 0; i < frameCount; i++)
	{
		video >> tempFrame;

		if (i % (frameCount / NUM_OF_FRAMES) == 0)
		{
			leftArr.push_back(tempFrame.clone());
			leftArr.back() = leftArr.back()(rectLeft);

			rightArr.push_back(tempFrame.clone());
			rightArr.back() = rightArr.back()(rectRight);
		}
	}

	//tempFrame.release();
	cout << "Stitching..." << endl;

	Stitcher stitcher = Stitcher::createDefault();

	Stitcher::Status status = stitcher.stitch(leftArr, leftPano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images in leftArr, error code = " << int(status) << endl;
		system("pause");
		return -1;
	}

	status = stitcher.stitch(rightArr, rightPano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images in rightArr, error code = " << int(status) << endl;
		system("pause");
		return -1;
	}

	imwrite("output/winter/leftPano.jpg", leftPano);
	imwrite("output/winter/rightPano.jpg", rightPano);

	endTime = clock();
	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;

	system("pause");
	return 0;
} // End main.