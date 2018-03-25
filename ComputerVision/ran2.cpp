//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//
//int main()
//{
//	// To measure the time elapsed.
//	clock_t startTime, endTime;
//	startTime = clock();
//
//	// Source video
//	string filename = "input/mountain.mov";
//	VideoCapture video(filename);
//
//	// Check if exist.
//	if (!video.isOpened())
//	{
//		cout << "Error when reading the video file..";
//		return -1;
//	}
//
//	// Stitch parameters.
//	bool try_use_gpu = true;
//	Stitcher::Mode mode = Stitcher::PANORAMA;
//
//	vector<Mat> leftArr, rightArr;
//	Mat tempFrame;
//	Mat leftPano;
//	Mat rightPano;
//
//	//const int NUM_OF_FRAMES = 20;
//	//const double STRIP_WIDTH = 0.6; // Percent
//
//	int frameCount = video.get(CV_CAP_PROP_FRAME_COUNT);
//	int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
//	int height = video.get(CV_CAP_PROP_FRAME_HEIGHT) - 1;
//
//	//Rect rectLeft(Point(0, 0), Point(width * STRIP_WIDTH, height));
//	//Rect rectRight(Point(width * (1 - STRIP_WIDTH), 0), Point(width, height));
//
//	int fromFrame = 115;
//	int toFrame = 329;
//
//	for (int i = 0; i < frameCount; i++)
//	{
//		video >> tempFrame;
//
//		if
//
//		rotate(tempFrame, tempFrame, 0);
//
//		leftArr.push_back(tempFrame.clone());
//		//leftArr.back() = leftArr.back()(rectLeft);
//
//		rightArr.push_back(tempFrame.clone());
//		//rightArr.back() = rightArr.back()(rectRight);
//	}
//
//	cout << "Stitching..." << endl;
//	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
//
//	Stitcher::Status status = stitcher->stitch(leftArr, leftPano);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't stitch images in leftArr, error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	/*status = stitcher->stitch(rightArr, rightPano);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't stitch images in rightArr, error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}*/
//
//	imwrite("output/winter/leftPano.jpg", leftPano);
//	//imwrite("output/winter/rightPano.jpg", rightPano);
//
//	endTime = clock();
//	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;
//
//	system("pause");
//	return 0;
//} // End main.