//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//using namespace cv::detail;
//
//vector<Mat> GetFramesFromVideo();
//void CreatePanorama(vector<Mat> &framesVector);
//
//int main(int argc, char** argv)
//{
//	// To measure the time elapsed.
//	clock_t startTime, endTime;
//	startTime = clock();
//
//	vector<Mat> framesArr = GetFramesFromVideo();
//
//	CreatePanorama(framesArr);
//
//	endTime = clock();
//	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;
//
//	system("pause");
//	return 0;
//}
//
//
//vector<Mat> GetFramesFromVideo()
//{
//	// Source video
//	string filename = "input/mountain.mov";
//	VideoCapture video(filename);
//
//	// Check if exist.
//	if (!video.isOpened())
//	{
//		cout << "Error when reading the video file..";
//	}
//
//	// Get info from source video.
//	int frameCount = video.get(CV_CAP_PROP_FRAME_COUNT);
//
//	vector<Mat> framesArr;
//	Mat tempFrame;
//
//	const int startFrame = 115;
//	const int endFrame = 329;
//	const int frameSamplingRate = 8;
//
//	for (int i = 0; i < frameCount; i++)
//	{
//		video >> tempFrame;
//
//		if (i >= startFrame && i <= endFrame && i % frameSamplingRate == 0)
//		{
//			rotate(tempFrame, tempFrame, 0);
//			framesArr.push_back(tempFrame.clone());
//		}
//	}
//
//	return framesArr;
//}
//
//
//void CreatePanorama(vector<Mat> &framesVector)
//{
//	// Stitcher parameters.
//	bool try_use_gpu = true;
//	Stitcher::Mode mode = Stitcher::PANORAMA;
//
//	int height = framesVector[0].rows;
//	int width = framesVector[0].cols;
//
//	vector<Mat> leftFramesArr1, leftFramesArr2;
//	vector<Mat> rightFramesArr1, rightFramesArr2;
//
//	// In percent.
//	const double STRIP_WIDTH = 0.99;
//
//	// Create strips size.			
//	Rect rectLeft(Point(0, 0), Point(width * STRIP_WIDTH, height));
//	//Rect rectRight(Point(width * (1 - STRIP_WIDTH), 0), Point(width, height));
//
//
//	for (int i = 0; i < framesVector.size(); i++)
//	{
//		if (i < framesVector.size() / 2)
//		{
//			leftFramesArr1.push_back(framesVector[i](rectLeft));
//
//			//rightFramesArr1.push_back(framesVector[i](rectRight));
//		}
//		else if (i == framesVector.size() / 2)
//		{
//			leftFramesArr1.push_back(framesVector[i](rectLeft));
//			leftFramesArr2.push_back(framesVector[i](rectLeft));
//
//			//rightFramesArr1.push_back(framesVector[i](rectRight));
//			//rightFramesArr2.push_back(framesVector[i](rectRight));
//		}
//		else
//		{
//			leftFramesArr2.push_back(framesVector[i](rectLeft));
//
//			//rightFramesArr2.push_back(framesVector[i](rectRight));
//		}
//	}
//
//	// Create stitcher object.
//	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
//
//	Ptr<ExposureCompensator> exposure_compensator = ExposureCompensator::createDefault(ExposureCompensator::GAIN_BLOCKS);
//	stitcher.setExposureCompensator(exposure_compensator);
//
//	stitcher.setPanoConfidenceThresh(1);
//	stitcher.setSeamEstimationResol(0.08);
//
//	stitcher.setWaveCorrection(true);
//	stitcher.setWaveCorrectKind(detail::WAVE_CORRECT_HORIZ);
//
//
//	cout << "Number of frame = " << framesVector.size() << endl;
//	cout << "Strip size = " << STRIP_WIDTH << endl;
//
//	Mat firstHalfPano;
//	Mat secondHalfPano;
//	Mat finalPano;
//
//	// Left panorama.
//	cout << "Stitching first half of panaroma (left)..." << endl;
//	stitcher.estimateTransform(leftFramesArr1);
//	stitcher.composePanorama(leftFramesArr1, firstHalfPano);
//
//	cout << "Stitching second half of panorama (left)..." << endl;
//	stitcher.estimateTransform(leftFramesArr2);
//	stitcher.composePanorama(leftFramesArr2, secondHalfPano);
//
//	cout << "Stitching final panorama (left)..." << endl;
//	vector<Mat> tupple = { firstHalfPano ,secondHalfPano };
//	stitcher.estimateTransform(tupple);
//	stitcher.composePanorama(tupple, finalPano);
//
//	// Save res to computer.
//	imwrite("output/firstPanoLeft.jpg", firstHalfPano);
//	imwrite("output/secondPanoLeft.jpg", secondHalfPano);
//	imwrite("output/finalPanoLeft.jpg", finalPano);
//
//	//// Right panorama.
//	//// Create first half panorama.
//	//cout << "Stitching first half panaroma (right)..." << endl;
//	//stitcher.estimateTransform(rightFramesArr1);
//	//stitcher.composePanorama(rightFramesArr1, firstHalfPano);
//
//	//// Create second half Panorama.
//	//cout << "Stitching second half panorama (right)..." << endl;
//	//stitcher.estimateTransform(rightFramesArr2);
//	//stitcher.composePanorama(rightFramesArr2, secondHalfPano);
//
//	//// Create final panorama.
//	//cout << "Stitching final panorama (right)..." << endl;
//	//tupple = { firstHalfPano ,secondHalfPano };
//	//stitcher.estimateTransform(tupple);
//	//stitcher.composePanorama(tupple, finalPano);
//
//	//imwrite("output/firstPanoRight.jpg", firstHalfPano);
//	//imwrite("output/secondPanoRight.jpg", secondHalfPano);
//	//imwrite("output/finalPanoRight.jpg", finalPano);
//}
//
//
