#include <stdio.h>
#include <io.h>
#include <iostream>
#include<opencv\cv.h>
#include<opencv\cxcore.h>
#include<opencv2\opencv.hpp>
#include<highgui.h>
#include "opencv2/imgproc/imgproc_c.h" 
#include "opencv2/core/core_c.h"      
#include "opencv2/highgui/highgui_c.h"
using namespace cv;

class Neuron
{
	public: char name;
	public: int** input;
	public: int output;
	int** memory;
	public: Neuron(int f)
	{	
		name = ' ';
		int n = 30;
		input = new int*[n];
		for (int i = 0; i < n; i++)
		{
			input[i] = new int[n];
		}
	}
	
};
int main()
{	
	int n = 32;
	Neuron* net[33];
	char ch = 'A';
	uchar* data;
	net[0] = new Neuron(4);
	net[0]->name = 'A';
	for (int i = 0; i < n; i++)
	{
		net[i] = new Neuron(4);
		net[i]->output = 0;
		net[i]->name = ch++;
	}
	IplImage *img = cvLoadImage("1.jpg");
	CvScalar s;
	for (int y=0;y<30;y++)
		for (int x = 0; x < 30; x++)
		{
			data = (uchar*)img->imageData;
		}
	system("pause");
	
//		neuro_web[i] : = Neuron.Create;
//	neuro_web[i].output: = 0; //  Пусть пока молчит
	//neuro_web[i].name: = chr(Ord('A') + i); // Буквы от А до Я
	//end;
}