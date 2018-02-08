//#include <opencv2/opencv.hpp>
//#include <iostream>
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
//	int frameCount = capture.get(CV_CAP_PROP_FRAME_COUNT);
//	int width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
//	int height = capture.get(CV_CAP_PROP_FRAME_HEIGHT) - 1;
//
//	const int NUM_OF_FRAMES = 10;
//	const int STRIP_WIDTH = 500; /// change to percent
//
//	// Get frames from source video.
//	for (int i = 0; ; i++)
//	{
//		capture >> tempFrame;
//
//		if (tempFrame.empty())
//			break;
//
//		if (i % (frameCount / NUM_OF_FRAMES) == 0)
//			framesArr.push_back(tempFrame.clone());
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
//	cout << "Before stitching..." << endl;
//
//	// Stitching all frames into one panorama.
//	Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA, true);
//	//Stitcher::Status status = stitcher->stitch(framesArr, panorama);
//
//	vector<Mat> framesArr2;
//	framesArr2.push_back(framesArr[0].clone());
//	framesArr2.push_back(framesArr[1].clone());
//
//	for (int i = 0; i < framesArr.size() - 2; i++)
//	{
//		Stitcher::Status status = stitcher->stitch(framesArr2, panorama);
//
//		if (status != Stitcher::OK)
//			break;
//
//		framesArr2[0] = panorama.clone();
//		framesArr2[1] = framesArr[i + 2].clone();
//	}
//
//	cout << "After stitching!" << endl;
//
//	//if (status != Stitcher::OK)
//	//{
//	//	cout << "Can't stitch images, error code = " << int(status) << endl;
//	//	//return -1;
//	//	system("pause");
//	//}
//
//	//destroyAllWindows();
//	//namedWindow(windowName, WINDOW_KEEPRATIO);
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
