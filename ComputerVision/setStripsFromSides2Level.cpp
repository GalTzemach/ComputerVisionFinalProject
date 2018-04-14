//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//
//int main()
//{
//	// My var.
//	const double STRIP_WIDTH = 0.99;
//	const int frameSamplingRate = 8;
//
//	const int startFrame = 115;
//	const int endFrame = 329;
//
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
//	// Stitcher parameters.
//	bool try_use_gpu = true;
//	Stitcher::Mode mode = Stitcher::PANORAMA;
//
//	// For hold the relevant frame/s.
//	vector<Mat> leftFrameArr, rightFrameArr;
//	Mat tempFrame;
//	Mat leftPano, leftPano1, leftPano2;
//	Mat rightPano, rightPano1, rightPano2;
//
//	// Get info from source video.
//	int frameCount = video.get(CV_CAP_PROP_FRAME_COUNT);
//	// Height and width are Opposite - Because the video is tilted 90 degrees.
//	int height = video.get(CV_CAP_PROP_FRAME_WIDTH);
//	int width = video.get(CV_CAP_PROP_FRAME_HEIGHT);
//
//	// Create strips size.
//	Rect rectLeft(Point(0, 0), Point(width * STRIP_WIDTH, height));
//	Rect rectRight(Point(width * (1 - STRIP_WIDTH), 0), Point(width, height));
//
//	// Fill selected strips into arrays.
//	for (int i = 0; i < frameCount; i++)
//	{
//		video >> tempFrame;
//
//		if (i >= startFrame && i <= endFrame && i % frameSamplingRate == 0)
//		{
//			rotate(tempFrame, tempFrame, 0);
//
//			leftFrameArr.push_back(tempFrame.clone()(rectLeft));
//
//			rightFrameArr.push_back(tempFrame.clone()(rectRight));
//		}
//	}
//
//	cout << "Number of frame = " << leftFrameArr.size() << endl;
//	cout << "Strip size = " << STRIP_WIDTH << endl;
//
//	// Divide to two parts.
//	vector<Mat> leftFrameArr1, leftFrameArr2;
//	vector<Mat> rightFrameArr1, rightFrameArr2;
//
//	for (int i = 0; i < leftFrameArr.size(); i++)
//	{
//		if (i < leftFrameArr.size() / 2)
//		{
//			leftFrameArr1.push_back(leftFrameArr[i]);
//
//			rightFrameArr1.push_back(rightFrameArr[i]);
//		}
//		else if (i == leftFrameArr.size() / 2)
//		{
//			leftFrameArr1.push_back(leftFrameArr[i]);
//			leftFrameArr2.push_back(leftFrameArr[i]);
//
//			rightFrameArr1.push_back(rightFrameArr[i]);
//			rightFrameArr2.push_back(rightFrameArr[i]);
//		}
//		else
//		{
//			leftFrameArr2.push_back(leftFrameArr[i]);
//
//			rightFrameArr2.push_back(rightFrameArr[i]);
//		}
//	}
//
//	// Stitching all frames into one panorama.
//	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
//	Stitcher::Status status;
//
//	// Left panorama.
//	cout << "Stitching left panorama..." << endl;
//
//	// Part 1.
//	cout << "estimateTransform (part 1)..." << endl;
//	status = stitcher->estimateTransform(leftFrameArr1);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't estimateTransform in leftFrameArr1 (part 1), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	cout << "composePanorama (part 1)..." << endl;
//	status = stitcher->composePanorama(leftFrameArr1, leftPano1);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't composePanorama in leftFrameArr1 (part 1), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	// Part 2.
//	cout << "estimateTransform (part 2)..." << endl;
//	status = stitcher->estimateTransform(leftFrameArr2);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't estimateTransform in leftFrameArr2 (part 2), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	cout << "composePanorama (part 2)..." << endl;
//	status = stitcher->composePanorama(leftFrameArr2, leftPano2);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't composePanorama in leftFrameArr2 (part 2), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	// Final left.
//	leftFrameArr = { leftPano1, leftPano2 };
//
//	cout << "estimateTransform (final left pano)..." << endl;
//	status = stitcher->estimateTransform(leftFrameArr);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't estimateTransform in leftFrameArr (final pano), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	cout << "composePanorama (final left pano)..." << endl;
//	status = stitcher->composePanorama(leftFrameArr, leftPano);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't composePanorama in leftFrameArr (final pano), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	// Save left results to computer.
//	imwrite("output/leftPano.jpg", leftPano);
//
//
//
//	// Right panorama.
//	cout << "Stitching right panorama..." << endl;
//
//	// Part 1.
//	cout << "estimateTransform (part 1)..." << endl;
//	status = stitcher->estimateTransform(rightFrameArr1);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't estimateTransform in rightFrameArr1 (part 1), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	cout << "composePanorama (part 1)..." << endl;
//	status = stitcher->composePanorama(rightFrameArr1, rightPano1);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't composePanorama in rightFrameArr1 (part 1), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	// Part 2.
//	cout << "estimateTransform (part 2)..." << endl;
//	status = stitcher->estimateTransform(rightFrameArr2);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't estimateTransform in rightFrameArr2 (part 2), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	cout << "composePanorama (part 2)..." << endl;
//	status = stitcher->composePanorama(rightFrameArr2, rightPano);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't composePanorama in rightFrameArr2 (part 2), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	// Final right.
//	leftFrameArr = { rightPano1, rightPano2 };
//
//	cout << "estimateTransform (final right pano)..." << endl;
//	status = stitcher->estimateTransform(rightFrameArr);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't estimateTransform in rightFrameArr (final pano), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	cout << "composePanorama (final right pano)..." << endl;
//	status = stitcher->composePanorama(rightFrameArr, rightPano);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't composePanorama in rightFrameArr (final pano), error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	// Save right results to computer.
//	imwrite("output/rightPano.jpg", rightPano);
//
//	// Print time elapsed
//	endTime = clock();
//	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;
//
//	system("pause");
//	return 0;
//} // End main.