#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{
	// To measure the time elapsed.
	clock_t startTime, endTime;
	startTime = clock();

	// Source video
	string filename = "input/mountain.mov";
	VideoCapture video(filename);

	// Check if exist.
	if (!video.isOpened())
	{
		cout << "Error when reading the video file..";
		return -1;
	}

	//const int NUM_OF_FRAMES = 150;
	const double STRIP_WIDTH = 0.6; /// In percent.
	const int startFrame = 115;
	const int endFrame = 329;

	// Stitching parameters.
	bool try_use_gpu = true;
	Stitcher::Mode mode = Stitcher::PANORAMA;

	vector<Mat> leftArr, rightArr;
	Mat tempFrame;
	Mat leftPano;
	Mat rightPano;

	// Get info from source video.
	int frameCount = video.get(CV_CAP_PROP_FRAME_COUNT);
	// Opposite - Because video is tilted 90 degrees.
	int height = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int width = video.get(CV_CAP_PROP_FRAME_HEIGHT);

	// Create strips size.
	Rect rectLeft(Point(0, 0), Point(width * STRIP_WIDTH, height));
	Rect rectRight(Point(width * (1 - STRIP_WIDTH), 0), Point(width, height));

	// Fill selected strips into arrays.
	for (int i = 0; i < frameCount; i++)
	{
		video >> tempFrame;

		if (i >= startFrame && i <= endFrame && i % 6 == 0)
		{
			rotate(tempFrame, tempFrame, 0);

			leftArr.push_back(tempFrame.clone()(rectLeft));

			rightArr.push_back(tempFrame.clone()(rectRight));
		}
	}

	cout << "Number of frame = " << leftArr.size() << endl;
	cout << "Strip size = " << STRIP_WIDTH << endl;

	cout << "Stitching..." << endl;

	// Stitching all frames into one panorama.
	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
	Stitcher::Status status;

	status = stitcher->stitch(leftArr, leftPano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images in leftArr, error code = " << int(status) << endl;
		system("pause");
		return -1;
	}

	status = stitcher->stitch(rightArr, rightPano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images in rightArr, error code = " << int(status) << endl;
		system("pause");
		return -1;
	}

	imwrite("output/leftPano.jpg", leftPano);
	imwrite("output/rightPano.jpg", rightPano);

	endTime = clock();
	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;

	system("pause");
	return 0;
} // End main.