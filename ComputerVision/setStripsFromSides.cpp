#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void stereoPanorama(Mat leftPano, Mat rightPano);

int main()
{
	// My var.
	const double STRIP_WIDTH = 0.99;
	const int FRAME_SAMPLING_RATE = 12;

	const int START_FRAME = 115;
	const int END_FRAME = 329;

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
	vector<Mat> leftArr, rightArr;
	Mat tempFrame;
	Mat leftPano;
	Mat rightPano;
	Mat leftRrightPano;

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

		if (i >= START_FRAME && i <= END_FRAME && i % FRAME_SAMPLING_RATE == 0)
		{
			rotate(tempFrame, tempFrame, 0);

			leftArr.push_back(tempFrame.clone()(rectLeft));

			rightArr.push_back(tempFrame.clone()(rectRight));
		}
	}

	cout << "Number of frame = " << leftArr.size() << endl;
	cout << "Strip size = " << STRIP_WIDTH << endl;

	// Stitching all frames into one panorama.
	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
	Stitcher::Status status;

	cout << "Stitching left panorama..." << endl;
	status = stitcher->stitch(leftArr, leftPano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch frames in leftArr, error code = " << int(status) << endl;
		system("pause");
		return -1;
	}

	cout << "Stitching right panorama..." << endl;
	status = stitcher->stitch(rightArr, rightPano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch frames in rightArr, error code = " << int(status) << endl;
		system("pause");
		return -1;
	}

	// Makes the panorama images same size if needed.
	if (leftPano.size < rightPano.size)
		resize(rightPano, rightPano, leftPano.size());
	else if (rightPano.size < leftPano.size)
		resize(leftPano, leftPano, rightPano.size());

	// vertical concatenation.
	vconcat(leftPano, rightPano, leftRrightPano);

	// Save results to computer.
	imwrite("output/leftPano.jpg", leftPano);
	imwrite("output/rightPano.jpg", rightPano);
	imwrite("output/leftRrightPano.jpg", leftRrightPano);

	stereoPanorama(leftPano, rightPano);

	// Print time elapsed.
	endTime = clock();
	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;

	system("pause");
	return 0;

} // End main.


// Code that converts two images into one stereoPanorama.
void stereoPanorama(Mat leftPano, Mat rightPano)
{
	Mat leftPanoChanels[3];
	Mat rightPanoChanels[3];

	Mat leftPanoCyan;
	Mat rightPanoRed;

	Mat stereoPanorama;

	// Split chanels.
	split(leftPano, leftPanoChanels);
	split(rightPano, rightPanoChanels);

	// Set the right pano to red color.
	rightPanoChanels[0] = Mat::zeros(rightPano.rows, rightPano.cols, CV_8UC1);//Set blue channel to 0
	rightPanoChanels[1] = Mat::zeros(rightPano.rows, rightPano.cols, CV_8UC1);//Set green channel to 0
	merge(rightPanoChanels, 3, rightPanoRed);

	// Set the left pano to cyan color.
	leftPanoChanels[2] = Mat::zeros(leftPano.rows, leftPano.cols, CV_8UC1);//Set red channel to 0
	merge(leftPanoChanels, 3, leftPanoCyan);

	// Add two images leftPanoCyan & rightPanoRed to one stereoPanorama
	add(leftPanoCyan, rightPanoRed, stereoPanorama);

	//Write the stereoPanorama 
	imwrite("output/stereoPanorama.jpeg", stereoPanorama);

} // End stereoPanorama