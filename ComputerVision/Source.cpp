#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// Source video
	string filename = "input/source.mp4";
	VideoCapture capture(filename);

	if (!capture.isOpened())
	{
		cout << "Error when reading the video file..";
		return 1;
	}

	String windowName = "Panorama";
	vector<Mat> framesArr;
	Mat tempFrame;
	Mat panorama;
	const int NUM_OF_FRAMES = 5;
	const int STRIP_WIDTH = 400; /// change to percent
	//const int STRIP_HEIGHT = 20;

	int frameCount = capture.get(CV_CAP_PROP_FRAME_COUNT);
	int width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CV_CAP_PROP_FRAME_HEIGHT) - 1;

	// Get frames from source video.
	for (int i = 0; ; i++)
	{
		capture >> tempFrame;
		if (tempFrame.empty())
			break;

		if (i % (frameCount / NUM_OF_FRAMES) == 0)
			framesArr.push_back(tempFrame.clone());

		//imwrite(to_string(i / 50) + ".jpg", frame.clone());
	}

	//// Select strip from each frame.
	//for (int i = 0; i < framesArr.size(); i++)
	//{
	//	tempFrame = framesArr[i].clone();
	//	Rect stripSize(Point((width - STRIP_WIDTH) / 2, 0), Point((width + STRIP_WIDTH) / 2, height));
	//	tempFrame = tempFrame(stripSize);
	//	framesArr[i] = tempFrame;
	//}


	// Stitching all frames into one panorama.
	Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA, true);
	Stitcher::Status status = stitcher->stitch(framesArr, panorama);

	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return -1;
	}

	//destroyAllWindows();
	//namedWindow(windowName, WINDOW_KEEPRATIO);
	imshow(windowName, panorama);
	imwrite("pano.jpg", panorama.clone());
	waitKey(0);

	return 0;
} // End main
