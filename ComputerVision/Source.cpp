#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// Source video
	string filename = "source.mp4";
	VideoCapture capture(filename);

	if (!capture.isOpened())
		cout << "Error when reading the video file..";

	String windowName = "Panorama";
	vector<Mat> framesArr;
	Mat tempFrame;
	Mat panorama;

	int numOfFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);

	// Get frames from source video.
	for (int i = 0; ; i++)
	{
		capture >> tempFrame;

		if (tempFrame.empty())
			break;

		if (i % (numOfFrames / 8) == 0)
			framesArr.push_back(tempFrame.clone());

		//imwrite(to_string(i / 50) + ".jpg", frame.clone());
	}

	// Stitching all frames into one panorama.
	Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA, true);
	Stitcher::Status status = stitcher->stitch(framesArr, panorama);

	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return -1;
	}

	//namedWindow(windowName, WINDOW_KEEPRATIO);
	imshow(windowName, panorama);
	imwrite("pano.jpg", panorama.clone());
	waitKey(0);

	return 0;
} // End main
