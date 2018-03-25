#include <stdio.h>
#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm> 

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	// opencv's panoromic stitching tools paramteres
	bool try_use_gpu = true;
	bool divide_images = false;
	int i = 0;

	// our aim is construct panaromic images rahter than just merging consecutive images
	Stitcher::Mode mode = Stitcher::PANORAMA;
	
	// image arrays to prenet stereo vsion as left and right eye signth
	vector<Mat> rMat;
	vector<Mat> lMat;

	// To read video we create a video reader object with given video file name
	VideoCapture vid = VideoCapture("input/mountain.mov");
	
	// check if the file is existing
	if (!vid.isOpened())
	{
		cout << "Can not open file !!" << endl;
		return 0;
	}

	// read all frame from the beginning to the end
	while (true)
	{
		Mat image;
		// read next image from video
		vid.read(image);

		// rotate 90 degree, since the original images are rotated
		rotate(image, image, 0);
		// check if we come to the end of the video
		if (image.empty())
		{
			cout << " Video is finihed  " << endl;
			break;
		}

		// write rotated frame to the file		
		std::stringstream ss;
		ss << std::setw(3) << std::setfill('0') << i;
		std::string number = ss.str();
		std::string name = "output/ran/mountain-" + number + ".jpg";
		imwrite(name, image);
		i++;
		cout << i << " th frame done " << endl;
	}

	// to make panormoric image stitching with opencv, we should not take all images, since it takes too long time 
	// in video all images is almost 3 full turn of all the envronment. So we need to selcet just one turn 
	// as my investigation of that images 127-347 th frames conssit of full 360 degree view so 
	// I selected those images to be stitch for left eye. Since the turn in that video is left to rigth, next frames consist of the view of the environment 
	// more right angle. I mean if we assume 1st frame is sensed by left eye then 2sn is right.
	// in that way I select 127 for left eye, 128 for right eye, 137 for left eye 138 for right eye. so on so forth.


	// start 127th frame from 347th frame 10 by 10
	int sframe = 127;
	int eframe = 347;

	for (int i = sframe; i <= eframe; i = i + 10)
	{
		// read concerned order of image from folder 
		std::stringstream ss;
		ss << std::setw(3) << std::setfill('0') << i;
		std::string number = ss.str();

		std::string name = "output/ran/mountain-" + number + ".jpg";

		Mat img = imread(name);

		// put image in to left eye sensed frames array
		lMat.push_back(img);
	}

	// for left eye start 128th frame from 348th frame 10 by 10
	// since the images collected from left to right, so we assume following images is so called left image.
	// for example 127th image is collected by right eye, 128th image is collected by left eye
	for (int i = sframe + 1; i <= eframe + 1; i = i + 10)
	{
		// read concerned order of image from folder 
		std::stringstream ss;
		ss << std::setw(3) << std::setfill('0') << i;
		std::string number = ss.str();

		std::string name = "output/ran/mountain-" + number + ".jpg";

		Mat img = imread(name);

		// put image in to right eye sensed frames array
		rMat.push_back(img);
	}

	Mat panoroma1, panoroma2;
	// create stitcher object with of params
	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
	// run opencv's panaromic stitching api for left eye
	Stitcher::Status status1 = stitcher->stitch(lMat, panoroma1);

	if (status1 == Stitcher::OK)
	{
		// apply the same transformations for right eye. Note: we do not find any tranformation on this line.
		// just pply the transformation which was found by previous step.
		stitcher->composePanorama(rMat, panoroma2);
		// write panoromic image to the file
		imwrite("left_panoromic.jpg", panoroma1);
		imwrite("right_panoromic.jpg", panoroma2);
	}
	else
	{
		cout << "Stitching failed!!" << endl;
	}

	return 0;
}
