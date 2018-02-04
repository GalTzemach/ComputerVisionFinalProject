#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	String windowName = "Panorama";

	// Source video
	string filename = "source.mp4";
	VideoCapture capture(filename);

	if (!capture.isOpened())
		cout << "Error when reading the video file..";


	vector<Mat> framesArr;
	Mat frame;
	Mat panorama;

	//int fps = capture.get(CV_CAP_PROP_FPS);
	//int imageDuration = 1000 / fps;

	int numOfFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);

	for (int i = 0; ; i++)
	{
		capture >> frame;

		if (frame.empty())
			break;

		if (i > 0 && i % (numOfFrames / 6) == 0)
		{
			framesArr.push_back(frame.clone());
			//imwrite(to_string(i / 50) + ".jpg", frame.clone());
		}

		//imshow(windowName, frame);
		//waitKey(imageDuration); // waits to display frame
	}

	cout << "Num of frames = " << framesArr.size() << endl;

	
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
