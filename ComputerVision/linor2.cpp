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

	const int NUM_OF_FRAMES = 10;
	//const int STRIP_WIDTH = 350; /// change to percent

	int frameCount = video.get(CV_CAP_PROP_FRAME_COUNT);
	int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = video.get(CV_CAP_PROP_FRAME_HEIGHT) - 1;

	Rect rectLeft(Point(0, 0), Point(width*0.7, height));
	Rect rectRight(Point(width*0.3, 0), Point(width, height));

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

		/*char c = (char)waitKey(int(video.get(CV_CAP_PROP_FPS)));
		if (c == 27)
			break;*/
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

	imwrite("output/linor/leftPano.jpg", leftPano);
	imwrite("output/linor/rightPano.jpg", rightPano);

	endTime = clock();
	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;

	system("pause");
	return 0;
} // End main.