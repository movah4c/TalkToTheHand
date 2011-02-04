//VERSION: HAND DETECTION 1.0

//AUTHOR: ANDOL LI

//PROJECT: HAND DETECTION PROTOTYPE

//LAST UPDATED: 03/2009



#include "cv.h"

#include "cxcore.h"

#include "highgui.h"

#include "math.h"

#include <iostream>

#include <stdio.h>

#include <string.h>

#include <sstream>




using namespace std;

/*

--------------------------------------------*/

int main()

{

	int c = 0;

    CvCapture* capture = cvCaptureFromCAM(0);

		if(!cvQueryFrame(capture)){ cout<<"Video capture failed, please check the camera."<<endl;}else{cout<<"Video camera capture status: OK"<<endl;};

    CvSize sz = cvGetSize(cvQueryFrame( capture));

	IplImage* src = cvCreateImage( sz, 8, 3 );

	IplImage* hsv_image = cvCreateImage( sz, 8, 3);

	IplImage* hsv_mask = cvCreateImage( sz, 8, 1);

	CvScalar  hsv_min = cvScalar(0, 30, 80, 0);

	CvScalar  hsv_max = cvScalar(20, 150, 255, 0);

	//////

	while( c != 27)

	{

		src = cvQueryFrame( capture);

			cvNamedWindow( "src",1); cvShowImage( "src", src);

		cvCvtColor(src, hsv_image, CV_BGR2HSV);

			cvNamedWindow( "hsv-img",1); cvShowImage( "hsv-img", hsv_image);

		cvInRangeS (hsv_image, hsv_min, hsv_max, hsv_mask);

			cvNamedWindow( "hsv-msk",1); cvShowImage( "hsv-msk", hsv_mask); hsv_mask->origin = 1; 

			



		c = cvWaitKey( 10);

	}

	//////

	cvReleaseCapture( &capture);

	cvDestroyAllWindows();



}

