//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	clock_t startTime, endTime;
//	startTime = clock();
//
//	// Source video
//	string filename = "input/source.mp4";
//	VideoCapture capture(filename);
//
//	if (!capture.isOpened())
//	{
//		cout << "Error when reading the video file..";
//		return 1;
//	}
//
//	String windowName = "Panorama";
//	vector<Mat> framesArr;
//	Mat tempFrame;
//	Mat panorama;
//
//	//const int NUM_OF_FRAMES = 20;
//	const int STRIP_WIDTH = 10; /// change to percent
//
//	int frameCount = capture.get(CV_CAP_PROP_FRAME_COUNT);
//	int width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
//	int height = capture.get(CV_CAP_PROP_FRAME_HEIGHT) - 1;
//
//	// Get frames from source video.
//	for (int i = 0; ; i++)
//	{
//		capture >> tempFrame;
//
//		if (tempFrame.empty())
//			break;
//
//		framesArr.push_back(tempFrame.clone());
//	}
//
//	// Select strip from each frame.
//	for (int i = 0; i < framesArr.size(); i++)
//	{
//		tempFrame = framesArr[i].clone();
//		Rect stripSize(Point((width - STRIP_WIDTH) / 2, 0), Point((width + STRIP_WIDTH) / 2, height));
//		tempFrame = tempFrame(stripSize);
//		framesArr[i] = tempFrame;
//	}
//
//	reverse(framesArr.begin(), framesArr.end());
//
//	// Concat all frames.
//	hconcat(framesArr, panorama);
//
//	imshow(windowName, panorama);
//	imwrite("pano.jpg", panorama.clone());
//
//	endTime = clock();
//	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;
//
//	waitKey(0);
//
//	return 0;
//} // End main
