////#include <stdio.h>
////#include <iostream>
//
////#include "opencv/cv.hpp"
////#include "opencv/cxcore.hpp"
////#include "opencv2/highgui.hpp"
////#include "opencv2/stitching.hpp"
////#include "opencv2/core.hpp"
////#include "opencv2/imgproc.hpp"
////#include "opencv2/highgui.hpp"
////#include "opencv2/features2d.hpp"
////#include "opencv2/opencv_modules.hpp"
////#include "opencv2/opencv.hpp"
////#include "cropper.h"
////#include "Panorama.h"
////#include <string>
////#include <iomanip>
////#include <sstream>
//
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//using namespace cv::detail;
//
//vector<Mat> takeFramesFromVideo()
//{
//	VideoCapture videoCapture = VideoCapture("input/mountain.mov");
//	vector<Mat> framesVector;
//
//	for (;;)
//	{
//		Mat tempFrame;
//		videoCapture >> tempFrame; // get a new frame from video
//
//		if (tempFrame.empty()) break;
//
//		else
//		{
//			// frame rotation
//			transpose(tempFrame, tempFrame);
//			flip(tempFrame, tempFrame, 1);
//			framesVector.push_back(tempFrame);
//		}
//	}
//	return framesVector;
//}
//
//Mat makePanoramaL(vector<Mat> &framesVector)
//{
//	bool try_use_gpu = true;
//	Stitcher::Mode mode = Stitcher::PANORAMA;
//
//	float y_axis = framesVector[0].rows;
//	float x_axis = framesVector[0].cols / 100;
//
//	vector<Mat> leftFramesVector1;
//	vector<Mat> leftFramesVector2;
//
//	for (int i = 129; i <= 225; i += 8)  //125-x4 - 325 // 127-0x
//	{
//		leftFramesVector1.push_back(framesVector[i](Rect(0, 0, x_axis * 98, framesVector[i].rows))); //cut the right side // 
//																									 //imwrite("imgs/img" + to_string(i) +".jpg", leftFramesVector1.back());
//	}
//
//	for (int i = 224; i <= 320; i += 8)  //125-x4 - 325 // 127-0x
//	{
//		leftFramesVector2.push_back(framesVector[i](Rect(0, 0, x_axis * 98, framesVector[i].rows))); //cut the right side // 
//	}
//
//	Mat panorama1;
//	Mat panorama2;
//	Mat Fullpanorama;
//
//	Stitcher stitcher = Stitcher::createDefault(try_use_gpu); // create a Stitcher object
//	stitcher.setPanoConfidenceThresh(1);
//	stitcher.setSeamEstimationResol(0.08);
//
//	Ptr<ExposureCompensator> exposure_compensator = ExposureCompensator::createDefault(ExposureCompensator::GAIN_BLOCKS);
//	stitcher.setExposureCompensator(exposure_compensator);
//	//BestOf2NearestMatcher matcher(try_use_gpu);
//
//	//sett wave correction
//	stitcher.setWaveCorrection(true);
//	stitcher.setWaveCorrectKind(detail::WAVE_CORRECT_HORIZ);
//
//	stitcher.estimateTransform(leftFramesVector1);
//	stitcher.composePanorama(leftFramesVector1, panorama1);
//
//	stitcher.estimateTransform(leftFramesVector1);
//	stitcher.composePanorama(leftFramesVector2, panorama2);
//
//	vector <Mat> tupple = { panorama1 ,panorama2 };
//	stitcher.estimateTransform(tupple);
//	stitcher.composePanorama(tupple, Fullpanorama);
//
//	imwrite("pano1.jpg", panorama1);
//	imwrite("pano2.jpg", panorama2);
//	imwrite("FullpanoramaL.jpg", Fullpanorama);
//
//	return Fullpanorama;
//}
//
//Mat makePanoramaR(vector<Mat> &framesVector)
//{
//	bool try_use_gpu = true;
//	Stitcher::Mode mode = Stitcher::PANORAMA;
//
//	float y_axis = framesVector[0].rows;
//	float x_axis = framesVector[0].cols / 100;
//
//	vector<Mat> leftFramesVector1;
//	vector<Mat> leftFramesVector2;
//
//	for (int i = 133; i <= 229; i += 8)  //125-x4 - 325 // 127-0x
//	{
//		leftFramesVector1.push_back(framesVector[i](Rect(x_axis * 2, 0, x_axis * 98, framesVector[i].rows))); //cut the right side // 
//																											  //imwrite("imgs/img" + to_string(i) +".jpg", leftFramesVector1.back());
//	}
//
//	for (int i = 229; i <= 325; i += 8)  //125-x4 - 325 // 127-0x
//	{
//		leftFramesVector2.push_back(framesVector[i](Rect(x_axis * 2, 0, x_axis * 98, framesVector[i].rows))); //cut the right side // 
//	}
//
//	Mat panorama1;
//	Mat panorama2;
//	Mat Fullpanorama;
//
//	Stitcher stitcher = Stitcher::createDefault(try_use_gpu); // create a Stitcher object
//	stitcher.setPanoConfidenceThresh(1);
//	stitcher.setSeamEstimationResol(0.08);
//	Ptr<ExposureCompensator> exposure_compensator = ExposureCompensator::createDefault(ExposureCompensator::GAIN_BLOCKS);
//	stitcher.setExposureCompensator(exposure_compensator);
//	BestOf2NearestMatcher matcher(try_use_gpu);
//	//sett wave correction
//	stitcher.setWaveCorrection(true);
//	stitcher.setWaveCorrectKind(detail::WAVE_CORRECT_HORIZ);
//
//	stitcher.estimateTransform(leftFramesVector1);
//	stitcher.composePanorama(leftFramesVector1, panorama1);
//
//	stitcher.estimateTransform(leftFramesVector1);
//	stitcher.composePanorama(leftFramesVector2, panorama2);
//
//	vector <Mat> tupple = { panorama1 ,panorama2 };
//	stitcher.estimateTransform(tupple);
//	stitcher.composePanorama(tupple, Fullpanorama);
//
//	return Fullpanorama;
//}
//
//void main(int argc, char** argv)
//{
//
//	Mat r = imread("FullpanoramaL.jpg");
//
//	//r= crop.crop(r);
//	//imwrite("l.jpg", r);
//
//	//argv[1] - video file name
//
//	vector<Mat> framesVector = takeFramesFromVideo();
//	Mat panorama;
//	panorama = makePanoramaL(framesVector);
//	//imwrite("FullpanoramaL.jpg", panorama);
//	//panorama = crop.crop(panorama);
//	//imwrite("2cut.jpg", panorama);
//
//
//	// program is complete
//	//system("PAUSE");
//
//}
