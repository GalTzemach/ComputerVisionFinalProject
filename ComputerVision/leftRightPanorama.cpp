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
	VideoCapture capture(filename);

	// Check if exist.
	if (!capture.isOpened())
	{
		cout << "Error when reading the video file..";
		return 1;
	}

	// Stitching parameters.
	bool try_use_gpu = true;
	Stitcher::Mode mode = Stitcher::PANORAMA;

	vector<Mat> framesArr, centerArr, leftArr, rightArr;
	Mat tempFrame;
	Mat pano;
	Mat leftPano;
	Mat rightPano;

	// Get info from source video.
	int frameCount = capture.get(CV_CAP_PROP_FRAME_COUNT);
	// Opposite - Because video is tilted 90 degrees.
	int height = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int width = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

	//const int NUM_OF_FRAMES = 150;
	const double STRIP_WIDTH = 0.3; /// In percent.
	const int fromFrame = 115;
	const int toFrame = 329;

	// Get selected frames from source video.
	for (int i = 0; ; i++)
	{
		capture >> tempFrame;

		// Check if this last frame in video.
		if (tempFrame.empty())
			break;

		// Choose frame in specific interval from video (360 degrees total).
		if (i >= fromFrame && i <= toFrame) {
			// Choose specific number of frame.
			//if (i % ((toFrame - fromFrame) / NUM_OF_FRAMES) == 0)
			//{
			rotate(tempFrame, tempFrame, 0);
			framesArr.push_back(tempFrame.clone());
			//}
		}
	}

	// Create strips size.
	Rect centerStripSize(Point(width / 2 - (STRIP_WIDTH * width / 2), 0), Point(width / 2 + (STRIP_WIDTH * width / 2), height));
	Rect leftStripSize(Point(width / 4 - (STRIP_WIDTH * width / 2), 0), Point(width / 4 + (STRIP_WIDTH * width / 2), height));
	Rect rightStripSize(Point(width / 4 * 3 - (STRIP_WIDTH * width / 2), 0), Point(width / 4 * 3 + (STRIP_WIDTH * width / 2), height));

	// Fill selected strips into arrays.
	for (int i = 0; i < framesArr.size(); i++)
	{
		centerArr.push_back(framesArr[i].clone()(centerStripSize));
		//centerArr[i] = centerArr[i](centerStripSize);

		leftArr.push_back(framesArr[i].clone()(leftStripSize));
		//leftArr[i] = leftArr[i](leftStripSize);

		rightArr.push_back(framesArr[i].clone()(rightStripSize));
		//rightArr[i] = rightArr[i](rightStripSize);
	}

	cout << "Number of frame = " << framesArr.size() << endl;
	cout << "Strip size = " << STRIP_WIDTH << endl;

	cout << "Before stitching..." << endl;

	// Stitching all frames into one panorama.
	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
	Stitcher::Status status;

	status = stitcher->stitch(centerArr, pano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		//return -1;
		system("pause");
	}

	status = stitcher->stitch(leftArr, leftPano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		//return -1;
		system("pause");
	}

	status = stitcher->stitch(rightArr, rightPano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		//return -1;
		system("pause");
	}

	cout << "After stitching!" << endl;

	// Save results as images.
	imwrite("output/pano.jpg", pano.clone());
	imwrite("output/Leftpano.jpg", leftPano.clone());
	imwrite("output/Rightpano.jpg", rightPano.clone());

	endTime = clock();
	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;

	waitKey(0);

	return 0;
} // End main
