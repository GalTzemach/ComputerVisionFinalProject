//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//
//using namespace std;
//using namespace cv;
//
//void stereoPanorama(Mat leftPano, Mat rightPano);
//
//int main()
//{
//	// For hold the relevant frame/s.
//	vector<Mat> leftArr, rightArr;
//	Mat tempFrame;
//	Mat leftPano;
//	Mat rightPano;
//	Mat leftRightPano;
//
//	leftPano = imread("input/leftPano.jpg");
//	rightPano = imread("input/rightPano.jpg");
//
//	// Makes the images on the same size if needed
//	if (leftPano.size < rightPano.size)
//		resize(rightPano, rightPano, leftPano.size());
//	else if (rightPano.size < leftPano.size)
//		resize(leftPano, leftPano, rightPano.size());
//
//	// vertical concatenation.
//	vconcat(leftPano, rightPano, leftRightPano);
//
//	stereoPanorama(leftPano, rightPano);
//	// Save results to computer.
//	imwrite("output/leftPano.jpg", leftPano);
//	imwrite("output/rightPano.jpg", rightPano);
//	imwrite("output/leftRrightPano.jpg", leftRightPano);
//
//	system("pause");
//	return 0;
//
//} // End main.
//
//// Code that converts two images into one stereoPanorama.
//void stereoPanorama(Mat leftPano, Mat rightPano)
//{
//	Mat leftPanoChanels[3];
//	Mat rightPanoChanels[3];
//
//	Mat leftPanoCyan;
//	Mat rightPanoRed;
//
//	Mat stereoPanorama;
//
//	// Split chanels.
//	split(leftPano, leftPanoChanels);
//	split(rightPano, rightPanoChanels);
//
//	// Set the right pano to red color.
//	rightPanoChanels[0] = Mat::zeros(rightPano.rows, rightPano.cols, CV_8UC1);//Set blue channel to 0
//	rightPanoChanels[1] = Mat::zeros(rightPano.rows, rightPano.cols, CV_8UC1);//Set green channel to 0
//	merge(rightPanoChanels, 3, rightPanoRed);
//
//	// Set the left pano to cyan color.
//	leftPanoChanels[2] = Mat::zeros(leftPano.rows, leftPano.cols, CV_8UC1);//Set red channel to 0
//	merge(leftPanoChanels, 3, leftPanoCyan);
//
//	// Add two images leftPanoCyan & rightPanoRed to one stereoPanorama
//	add(leftPanoCyan, rightPanoRed, stereoPanorama);
//
//	//Write the stereoPanorama 
//	imwrite("output/stereoPanorama.jpeg", stereoPanorama);
//
//} // End stereoPanorama