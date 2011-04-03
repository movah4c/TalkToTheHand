#define CV_NO_BACKWARD_COMPATIBILITY

#include "cv.h"
#include "highgui.h"
#include <string.h>
#include <iostream>
#include <cstdio>

#ifdef _EiC
#define WIN32
#endif

using namespace std;
using namespace cv;

//prototype of the haar cascade function that uses xml to detect matches
void detectAndDraw( Mat& img,CascadeClassifier& cascade, double scale, char alpha);

//contains the cascade name
String cascadeName;
int cnt=0;


int main( int argc, const char** argv )
{
// variables declaration
    CvCapture* capture = 0;
    Mat frame, frameCopy, image;
    String inputName;
    CascadeClassifier cascade;
    double scale = 1;
    char alpha;
      
    //initiate camera to record
    capture = cvCaptureFromCAM(0);
    //creates window for displaying the output	
    cvNamedWindow( "result", 1 );

    //proceeds if capture from camera doesn't fail
    if( capture )
    {
        for(;;)
        {
	//captures frame by frame from the camera
            IplImage* iplImg = cvQueryFrame( capture );
            frame = iplImg;
            if( frame.empty() )
		{
		cout<<"IplImage* iplImg = cvQueryFrame( capture );\n failed";
                break;
		}
            if( iplImg->origin == IPL_ORIGIN_TL )
                frame.copyTo( frameCopy );
            else
                flip( frame, frameCopy, 0 );

	    //compares for 2 alphabets a and b
	    for(int i=0; i<2 ;i++)
	    {
		//compares for a
		if(i == 0)
		{
			cascadeName.assign("aGest.xml");
    			scale =3;
			alpha='a';
		}
		//compares for b
		else if(i == 1)
		{
			cascadeName.assign("bGest1.xml");
    			scale =4;
			alpha='b';			
		}
		//loads the cascade name and passes it to the haar cascade function for comparision
		cascade.load( cascadeName );
		detectAndDraw( frameCopy, cascade, scale ,alpha);
	    }

            if( waitKey( 10 ) >= 0 )
                break;
        }
	//releasing camera resource
        cvReleaseCapture( &capture );
    }
    else
    {
	cout<<"\ncapture from camera not successful\n";
	exit(0);
    }
	
    //release the window resources
    cvDestroyWindow("result");
    return 0;
}


//function the implements the haar cascade comparison
void detectAndDraw( Mat& img,CascadeClassifier& cascade,double scale, char alpha)
{
    int i = 0;
    double t = 0;
    vector<Rect> faces;
    const static Scalar colors[] =  { CV_RGB(0,0,255),
        CV_RGB(0,128,255),
        CV_RGB(0,255,255),
        CV_RGB(0,255,0),
        CV_RGB(255,128,0),
        CV_RGB(255,255,0),
        CV_RGB(255,0,0),
        CV_RGB(255,0,255)} ;
    Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );

    cvtColor( img, gray, CV_BGR2GRAY );
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    //histogram equalization
    equalizeHist( smallImg, smallImg );

    
    cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        //|CV_HAAR_FIND_BIGGEST_OBJECT
        //|CV_HAAR_DO_ROUGH_SEARCH
        |CV_HAAR_SCALE_IMAGE,
        Size(30, 30) );
    
    cout<<"detecting for the "<<cnt<<" time\n";
    cnt++;	
    for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
    {
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
	center.x = 0;
	center.y = 0;
        Scalar color = colors[i%8];
        int radius;
 
        center.x = cvRound((r->x + r->width*0.5)*scale);
        center.y = cvRound((r->y + r->height*0.5)*scale);
	radius = cvRound((r->width + r->height)*0.25*scale);
	//on positive comparison to the cascade
	if(center.x != 0 || center.y != 0)
		{
		cout<<alpha<<" Detected"<<endl;
	        circle( img, center, radius, color, 3, 8, 0 );
        	}
    }  
    cv::imshow( "result", img );    
}
