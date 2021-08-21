#include <iostream>
#include "opencv2\core\core.hpp"
#include "opencv2\core.hpp"
#include "opencv2\face.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\opencv.hpp"
#include<direct.h>
#include <vector>


using namespace std;
using namespace cv;
using namespace cv::face;

CascadeClassifier face_cascade;
CascadeClassifier eye_cascade;
Mat crop;
Mat cropface(Mat frame);
int i = 0,a;
vector<Rect> faces;
int main() {
	vector<Mat> img(10);
	vector<int> labels(10);
	vector<Mat> img2(10);
	VideoCapture cap(0);
	while (true) {
		if (i == 10) {
			break;
		}
		a = i;
		cap.read(img[a]);
		img2[a]=(cropface(img[a]));
		
		if (!faces.empty()) {
			rectangle(img[a], faces[0].tl(), faces[0].br(), Scalar(255, 0, 255), 3);
			i++;
		}
		imshow("ben", img[a]);
		labels[a] = 1;
		
		waitKey(1);
	}
	Mat img3 = imread("C:\\Users\\Gökhan\\Desktop\\New folder\\20200218_150206.jpg");
	img3=cropface(img3);

	int label = -1;
	double confidence_distance = 0;

	Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
	model->train(img2, labels);
	model->predict(img3, label, confidence_distance);
	cout << confidence_distance<<endl;
	
	if (confidence_distance<80) {
		cout << "resimler eþleþti";
	}
	else {
		cout << "resimler ayný kisiye ait degil";
	}
}
Mat cropface(Mat frame)
{

	Mat res;

	Mat gray;

	if (frame.channels() == 3) {
		cvtColor(frame, gray, COLOR_BGR2GRAY);
	}
	else if (frame.channels() == 4) {
		cvtColor(frame, gray, COLOR_BGR2GRAY);
	}
	else {

		gray = frame;
	}
	equalizeHist(gray, gray);
	face_cascade.load("C:\\Users\\Gökhan\\Desktop\\recoface-master\\classificadores\\haarcascades\\haarcascade_frontalface_alt.xml");
	if (face_cascade.empty()) {
		cout << "hata burda";
	}
	else {
		face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
		if (faces.empty()) {
		
			return (gray);
		}
		
		Rect roi_c;

		size_t ic = 0;

		
			roi_c.x = faces[ic].x;
			roi_c.y = faces[ic].y;
			roi_c.width = (faces[ic].width);
			roi_c.height = (faces[ic].height);
			




		
		
		
		crop = gray(roi_c);
		
		resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR);
		return(res);
	}
}
		
	