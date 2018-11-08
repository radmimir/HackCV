#include<opencv\cv.h>
#include<opencv\cxcore.h>
#include<opencv2\opencv.hpp>
#include<highgui.h>
#include "opencv2/imgproc/imgproc_c.h" 
#include "opencv2/core/core_c.h"      
#include "opencv2/highgui/highgui_c.h"
using namespace cv;
int main()
{
	IplImage* img = cvLoadImage("1.jpg");
	IplImage* src = cvCloneImage(img);
	// для хранения каналов HSV после преобразования
	IplImage* h_range = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* s_range = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* v_range = cvCreateImage(cvGetSize(img), 8, 1);
	double framemin=0, framemax=0;
	double Hmin, Hmax;
	double Smin, Smax;
	double Vmin, Vmax;

	cvShowImage("Исходное изображение", img);
	IplConvKernel* kern = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_ELLIPSE);
	cvDilate(img, src, kern, 2);
	IplImage* hsv = cvCreateImage(cvGetSize(img), 8, 3);
	IplImage* hsv_new = cvCreateImage(cvGetSize(img), 8, 3);
	IplImage* h_plane = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* s_plane = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* v_plane = cvCreateImage(cvGetSize(img), 8, 1);
	//  конвертируем в HSV 
	cvCvtColor(src, hsv, CV_BGR2HSV);
	// разбиваем на каналы
	cvSplit(hsv, h_plane, s_plane, v_plane, 0);


	cvMinMaxLoc(h_plane, &framemin, &framemax);
	Hmin = framemin;
	Hmax = framemax;
	cvMinMaxLoc(s_plane, &framemin, &framemax);
	Smin = framemin;
	Smax = framemax;
	cvMinMaxLoc(v_plane, &framemin, &framemax);
	Vmin = framemin;
	Vmax = framemax;
	/*
	cvShowImage("H", h_plane);
	cvShowImage("S", s_plane);
	cvShowImage("V", v_plane);
	cvThreshold(h_plane, h_range, 107, 146, CV_THRESH_BINARY);
	cvThreshold(s_plane, s_range, 100, 255, CV_THRESH_BINARY);
	cvThreshold(v_plane, v_range, 100, 255,CV_THRESH_BINARY);
	cvMerge()
	cvShowImage("hsv", hsv_new);
	//cvShowImage("h",h_plane);
	//cvShowImage("s", s_plane);
	//cvShowImage("v", v_plane);
	cvWaitKey(0);*/
	IplImage  *gray = 0, *dst = 0, *dst2 = 0;
	IplImage* r = 0, *g = 0, *b = 0; // для хранения отдельных слоёв RGB-изображения
	gray = cvCreateImage(cvGetSize(img), img->depth, 1);
	dst = cvCreateImage(cvGetSize(gray), IPL_DEPTH_8U, 1);
	dst2 = cvCreateImage(cvGetSize(gray), IPL_DEPTH_8U, 1);
	r = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	g = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	b = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);

	// разбиваем на отдельные слои
	cvSplit(img, b, g, r, 0);

	// картинка для хранения промежуточных результатов
	IplImage* temp = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);

	// складываем картинки с одинаковым весом
	cvAddWeighted(r, 1.0 / 3.0, g, 1.0 / 3.0, 0.0, temp);
	cvAddWeighted(temp, 2.0 / 3.0, b, 1.0 / 3.0, 0.0, temp);

	// выполняем пороговое преобразование 
	cvThreshold(temp, dst, 50, 250, CV_THRESH_BINARY);

	cvReleaseImage(&temp);

	// показываем результат
	cvNamedWindow("RGB cvThreshold", 1);
	cvShowImage("RGB cvThreshold", dst);

	//
	// попробуем пороговое преобразование над отдельными слоями
	//

	IplImage* t1, *t2, *t3; // для промежуточного хранения
	t1 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	t2 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	t3 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);

	// выполняем пороговое преобразование
	cvThreshold(r, t1, 107, 146, CV_THRESH_BINARY);
	cvThreshold(g, t2, 100, 255, CV_THRESH_BINARY);
	cvThreshold(b, t3, 100, 255, CV_THRESH_BINARY);

	// складываем результаты
	cvMerge(t3, t2, t1, 0, img);

	cvNamedWindow("RGB cvThreshold 2", 1);
	cvShowImage("RGB cvThreshold 2", img);

	cvReleaseImage(&t1); cvReleaseImage(&t2); cvReleaseImage(&t3);

	//=======================================================

	// ждём нажатия клавиши
	cvWaitKey(0);
	return 0;
}