#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "math.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

#include <sstream>
#include <time.h>

// Global storage
IplImage *IavgF, *IdiffF, *IprevF, *IhiF, *IlowF;
IplImage *Iscratch, *Iscratch2;
IplImage *Igray1, *Igray2, *Igray3;
IplImage *Ilow1, *Ilow2, *Ilow3;
IplImage *Ihi1, *Ihi2, *Ihi3;
IplImage *Imaskt;
float Icount;

// Function of allocating images
void AllocateImages( IplImage* I ){
	CvSize sz = cvGetSize( I );

	IavgF = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
	IdiffF = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
	IprevF = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
	IhiF = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
	IlowF = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
	Ilow1 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
	Ilow2 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
	Ilow3 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
	Ihi1 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
	Ihi2 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
	Ihi3 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
	cvZero( IavgF );
	cvZero( IdiffF );
	cvZero( IprevF );
	cvZero( IhiF );
	cvZero( IlowF );
	Icount = 0.0001;	// protect against divid by 0

	Iscratch= cvCreateImage( sz, IPL_DEPTH_32F, 3 );
	Iscratch2 = cvCreateImage( sz, IPL_DEPTH_32F, 3 );
	Igray1 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
	Igray2 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
	Igray3 = cvCreateImage( sz, IPL_DEPTH_32F, 1 );
	Imaskt = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
	cvZero( Iscratch );
	cvZero( Iscratch2 );
}

// Learn the background statistics for one more frame
void accumulateBackground( IplImage *I ){
	static int first = 1;
	cvCvtScale( I, Iscratch, 1, 0 );
	if( !first ){
		cvAcc( Iscratch, IavgF );
		cvAbsDiff( Iscratch, IprevF, Iscratch2 );
		cvAcc( Iscratch2, IdiffF );
		Icount += 1.0;
	}
	first = 0;
	cvCopy( Iscratch, IprevF );
}

void setHighThreshold( float scale ) {
	cvConvertScale( IdiffF, Iscratch, scale );
	cvAdd( Iscratch, IavgF, IhiF );
	cvSplit( IhiF, Ihi1, Ihi2, Ihi3, 0 );
}

void setLowThreshold( float scale ) {
	cvConvertScale( IdiffF, Iscratch, scale );
	cvAdd( Iscratch, IavgF, IlowF );
	cvSplit( IlowF, Ilow1, Ilow2, Ilow3, 0 );
}

void createModelsfromStats(){
	cvConvertScale( IavgF, IavgF, (double)(1.0/Icount) );
	cvConvertScale( IdiffF, IdiffF, (double)(1.0/Icount) );

	//Make sure diff is always something
	cvAddS( IdiffF, cvScalar( 1.0, 1.0, 1.0), IdiffF );
	setHighThreshold( 7.0 );
	setLowThreshold( 6.0 );
}

// Create a mask
void backgroundDiff( IplImage *I, IplImage *Imask ){
	cvCvtScale( I, Iscratch, 1, 0);
	cvSplit( Iscratch, Igray1, Igray2, Igray3, 0 );

	// channel 1
	cvInRange( Igray1, Ilow1, Ihi1, Imask );
	// channel 2
	cvInRange( Igray2, Ilow2, Ihi2, Imaskt );
	cvOr( Imask, Imaskt, Imask );
	// channel 3
	cvInRange( Igray3, Ilow3, Ihi3, Imaskt );
	cvOr( Imask, Imaskt, Imask );
}

void DeallocateImages()
{
	cvReleaseImage( &IavgF );
	cvReleaseImage( &IdiffF );
	cvReleaseImage( &IprevF );
	cvReleaseImage( &IhiF );
	cvReleaseImage( &IlowF );
	cvReleaseImage( &Ilow1 );
	cvReleaseImage( &Ilow2 );
	cvReleaseImage( &Ilow3 );
	cvReleaseImage( &Ihi1 );
	cvReleaseImage( &Ihi2 );
	cvReleaseImage( &Ihi3 );
	cvReleaseImage( &Iscratch );
	cvReleaseImage( &Iscratch2 );
	cvReleaseImage( &Igray1 );
	cvReleaseImage( &Igray2 );
	cvReleaseImage( &Igray3 );
	cvReleaseImage( &Imaskt );
}


int main(int argc, char* argv[])
{
	
	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage *frame, *mask1, *mask3;
	cvNamedWindow( "Background Averaging", CV_WINDOW_AUTOSIZE );	
	int frameCount = 0;
	while(1) {
		frameCount++;
		frame = cvQueryFrame( capture );
		if( !frame ) break;
		CvSize sz = cvGetSize( frame );
		mask1 = cvCreateImage( sz, IPL_DEPTH_8U, 1 );
		mask3 = cvCreateImage( sz, IPL_DEPTH_8U, 3 );
		if(frameCount == 1)
			AllocateImages( frame );
		

		if( frameCount < 30 ){
			accumulateBackground( frame );
		}else if( frameCount == 30 ){
			createModelsfromStats();
		}else{
			backgroundDiff( frame, mask1 );

			cvCvtColor(mask1,mask3,CV_GRAY2BGR);
			cvNorm( mask3, mask3, CV_C, 0);
			cvThreshold(mask3, mask3, 100, 1, CV_THRESH_BINARY);
			cvMul( frame, mask3, frame, 1.0 );
			cvShowImage( "Background Averaging", frame );
		}

		char c = cvWaitKey(33);
		if( c == 27 ) break;
	}
	cvReleaseCapture( &capture );
	cvDestroyWindow( "Background Averaging" );
	DeallocateImages();
}
