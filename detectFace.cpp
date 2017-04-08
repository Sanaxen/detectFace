#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat detectFaceInImage(Mat &image, string &cascade_file, std::vector<Mat>& facelist) 
{
	CascadeClassifier cascade;
	cascade.load(cascade_file);

	vector<Rect> faces;
	cascade.detectMultiScale(image, faces, 1.1, 3, 0, Size(20, 20));

	for (int i = 0; i < faces.size(); i++) 
	{
		Point p1(faces[i].x - 5, faces[i].y - 5);
		Point p2(faces[i].x + faces[i].width + 5, faces[i].y + faces[i].height + 5);
		rectangle(image, p1, p2, Scalar(0, 200, 0), 1, CV_AA);

		cv::Mat imgSub(image, Rect(p1, p2));
		facelist.push_back(imgSub);

		waitKey(0);
	}
	return image;
}


int main(int argc, char const *argv[]) 
{
	Mat image = imread(argv[1]);
	string filename = argv[2];
	
	std::vector<Mat> facelist;
	Mat detectFaceImage = detectFaceInImage(image, filename, facelist);


	for (int i = 0; i < facelist.size(); i++)
	{
		char f[256];
		sprintf(f, "%s_%03d.png", "face", i);
		cv::resize(facelist[i], facelist[i], cv::Size(), 32. / facelist[i].cols, 32. / facelist[i].rows, cv::INTER_CUBIC);
		imwrite(f, facelist[i]);
	}

	cv::resize(detectFaceImage, detectFaceImage, cv::Size(), 256. / detectFaceImage.cols, 256. / detectFaceImage.rows, cv::INTER_CUBIC);
	imshow("detect face", detectFaceImage);
	imwrite("detect_face.png", detectFaceImage);

	waitKey(0);

	return 0;
}
