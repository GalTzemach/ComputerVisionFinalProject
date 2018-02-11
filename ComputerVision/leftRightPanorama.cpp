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
//	string filename = "input/source2.mp4";
//	VideoCapture capture(filename);
//
//	if (!capture.isOpened())
//	{
//		cout << "Error when reading the video file..";
//		return 1;
//	}
//
//	String windowName = "Panorama";
//	vector<Mat> framesArr, centerArr, leftArr, rightArr;
//	Mat tempFrame;
//	Mat pano;
//	Mat leftPano;
//	Mat rightPano;
//
//	const int NUM_OF_FRAMES = 6;
//	const int STRIP_WIDTH = 350; /// change to percent
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
//		if (i % (frameCount / NUM_OF_FRAMES) == 0)
//			framesArr.push_back(tempFrame.clone());
//	}
//
//	// Select strip from each frame.
//	Rect centerStripSize(Point((width - STRIP_WIDTH) / 2, 0), Point((width + STRIP_WIDTH) / 2, height));
//	Rect leftStripSize(Point(((width / 2) - STRIP_WIDTH) / 2, 0), Point(((width / 2) + STRIP_WIDTH) / 2, height));
//	Rect rightStripSize(Point(((width / 2) - STRIP_WIDTH) / 2 + (width / 2), 0), Point(((width / 2) + STRIP_WIDTH) / 2 + (width / 2), height));
//
//	for (int i = 0; i < framesArr.size(); i++)
//	{
//		centerArr.push_back(framesArr[i].clone());
//		centerArr[i] = centerArr[i](centerStripSize);
//
//		leftArr.push_back(framesArr[i].clone());
//		leftArr[i] = leftArr[i](leftStripSize);
//
//		rightArr.push_back(framesArr[i].clone());
//		rightArr[i] = rightArr[i](rightStripSize);
//	}
//
//	cout << "Before stitching..." << endl;
//
//	// Stitching all frames into one panorama.
//	Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA, true);
//	
//	Stitcher::Status status = stitcher->stitch(centerArr, pano);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't stitch images, error code = " << int(status) << endl;
//		//return -1;
//		system("pause");
//	}
//
//	status = stitcher->stitch(leftArr, leftPano);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't stitch images, error code = " << int(status) << endl;
//		//return -1;
//		system("pause");
//	}
//
//	status = stitcher->stitch(rightArr, rightPano);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't stitch images, error code = " << int(status) << endl;
//		//return -1;
//		system("pause");
//	}
//	cout << "After stitching!" << endl;
//
//
//	//destroyAllWindows();
//	//namedWindow(windowName, WINDOW_KEEPRATIO);
//	imshow(windowName, pano);
//	imwrite("output/pano.jpg", pano.clone());
//	imwrite("output/Leftpano.jpg", leftPano.clone());
//	imwrite("output/Rightpano.jpg", rightPano.clone());
//
//	endTime = clock();
//	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;
//
//	waitKey(0);
//
//	return 0;
//} // End main
