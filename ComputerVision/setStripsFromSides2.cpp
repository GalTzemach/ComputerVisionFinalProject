#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{
	// My var.
	const double STRIP_WIDTH = 0.6;
	const int frameSamplingRate = 8;

	const int startFrame = 115;
	const int endFrame = 329;

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

	// Stitcher parameters.
	bool try_use_gpu = true;
	Stitcher::Mode mode = Stitcher::PANORAMA;

	// For hold the relevant frame/s.
	vector<Mat> leftFrameArr, rightFrameArr;
	Mat tempFrame, leftPano, rightPano;

	// Get info from source video.
	int frameCount = video.get(CV_CAP_PROP_FRAME_COUNT);
	// Height and width are Opposite - Because the video is tilted 90 degrees.
	int height = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int width = video.get(CV_CAP_PROP_FRAME_HEIGHT);

	// Create strips size.
	Rect rectLeft(Point(0, 0), Point(width * STRIP_WIDTH, height));
	Rect rectRight(Point(width * (1 - STRIP_WIDTH), 0), Point(width, height));

	// Fill selected strips into arrays.
	for (int i = 0; i < frameCount; i++)
	{
		video >> tempFrame;

		if (i >= startFrame && i <= endFrame && i % frameSamplingRate == 0)
		{
			rotate(tempFrame, tempFrame, 0);

			leftFrameArr.push_back(tempFrame.clone()(rectLeft));

			rightFrameArr.push_back(tempFrame.clone()(rectRight));
		}
	}

	cout << "Number of frame = " << leftFrameArr.size() << endl;
	cout << "Strip size = " << STRIP_WIDTH << endl;

	// Stitching all frames into one panorama.
	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
	Stitcher::Status status;

	cout << "Stitching left panorama..." << endl;

	status = stitcher->estimateTransform(leftFrameArr);
	if (status != Stitcher::OK)
	{
		cout << "Can't estimateTransform in leftFrameArr, error code = " << int(status) << endl;
		system("pause");
		return -1;
	}

	status = stitcher->composePanorama(leftFrameArr, leftPano);
	if (status != Stitcher::OK)
	{
		cout << "Can't composePanorama in leftFrameArr, error code = " << int(status) << endl;
		system("pause");
		return -1;
	}

	// Save results to computer.
	imwrite("output/leftPano.jpg", leftPano);
	//imwrite("output/rightPano.jpg", rightPano);

	// Print time elapsed
	endTime = clock();
	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;

	system("pause");
	return 0;
} // End main.