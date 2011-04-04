#include "cvaux.h"
#include "cxmisc.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cv.h>

/**Variables for Codebook Method**/
CvBGCodeBookModel* model = 0;
const int NCHANNELS = 3;

/** This sets what channels should be adjusted for background bounds**/
bool ch[NCHANNELS]={true,true,true}; 

/** Setting number of frames to learn Background **/
int nframesToLearnBG = 10;

void diff_pix(IplImage* image,IplImage* image2)
{
      /** Number of lines **/
      int nl= image2->height;
	  /** Total number of element per line **/
      int nc= image2->width * image2->nChannels; 
      /** Effective width **/
	  int step= image2->widthStep; 

      /** Get the pointer to the image buffer **/
 	
      for (int j = 0; j < nl; j++) {
 
	uchar* pSrc1 = (uchar*) (image->imageData + j * image->widthStep);
	uchar* pSrc2 = (uchar*) (image2->imageData + j * image2->widthStep);
	
		for (int k = 0; k < nc; k++) {
		/** Setting RGB components corresponding to black colored pixels of the gray scale image to zero **/
			if( pSrc1[k]==0)
			{
				pSrc2[3*k]=0;
				pSrc2[3*k+1]=0;
				pSrc2[3*k+2]=0;
			}
			
		}

	}
		
 }

void backgroundSubtraction()
	{
	/** yuvImage is for codebook method **/
    IplImage* rawImage = 0, *yuvImage = 0; 
    IplImage *ImaskCodeBook = 0,*ImaskCodeBookCC = 0,*ImaskCodeBook1 = 0;
    CvCapture* capture = 0;

    int c, n, nframes = 0;
	
	/** Creating a Codebook Model for background **/
    model = cvCreateBGCodeBookModel();
    
    /** Set color thresholds to default values **/
    model->modMin[0] = 3;
    model->modMin[1] = model->modMin[2] = 3;
    model->modMax[0] = 10;
    model->modMax[1] = model->modMax[2] = 10;
    model->cbBounds[0] = model->cbBounds[1] = model->cbBounds[2] = 10;

    bool pause1 = false;
    bool singlestep = false;

	printf("Capture from camera\n");
    capture = cvCaptureFromCAM( 0 );
  
    if( !capture )
    {
        printf( "Can not initialize video capturing\n\n" );
       
    }

	/** Main processing loop **/
    for(;;)
	{
        if( !pause1 )
        {
            rawImage = cvQueryFrame( capture );
            ++nframes;
            if(!rawImage) 
                break;
        }
        if( singlestep )
            pause1 = true;
        
        /**First time: **/
        if( nframes == 1 )
        {
            /** Codebook method allocation **/
            yuvImage = cvCloneImage(rawImage);
            ImaskCodeBook = cvCreateImage( cvGetSize(rawImage), IPL_DEPTH_8U, 1 );
            ImaskCodeBookCC = cvCreateImage( cvGetSize(rawImage), IPL_DEPTH_8U, 1 );
            cvSet(ImaskCodeBook,cvScalar(255));
            
            cvNamedWindow( "Raw", 1 );
          }
			/** YUV For codebook method **/
            cvCvtColor( rawImage, yuvImage, CV_BGR2YCrCb );
            /** This is where we build our background model **/
            
			/** Find the foreground if any **/
            if( nframes-1 >= nframesToLearnBG  )
            {
                /** Find foreground by codebook method **/
                cvBGCodeBookDiff( model, yuvImage, ImaskCodeBook );
                /** This part just to visualize bounding boxes and centers if desired **/
                cvCopy(ImaskCodeBook,ImaskCodeBookCC);	
                cvSegmentFGMask( ImaskCodeBookCC );
				/** Convert obtained grayscale image to colored image using pixel access method **/			
				diff_pix(ImaskCodeBookCC,rawImage);
				
            }
		
		    /** Update the background model till the specified number of frames **/
			else if( !pause1 && nframes-1 < nframesToLearnBG  )
                cvBGCodeBookUpdate( model, yuvImage );
			/** Clear stale **/
			else if( nframes-1 == nframesToLearnBG  )
                cvBGCodeBookClearStale( model, model->t/2 );
      
            
			/** Display the output image **/
			cvShowImage( "Raw", rawImage );
         
			/** User input: **/
			c = cvWaitKey(10)&0xFF;
			c = tolower(c);
			/** End processing on ESC, q or Q **/
			if(c == 'q')
            break;
			
			/** Else check for other user inputs **/
			switch( c )
			{
			case 'p':
				pause1 = !pause1;
				break;
			case ' ':
				cvBGCodeBookClearStale( model, 0 );
				nframes = 0;
				break;
        }
		
    }		
	/** Capture release **/
    cvReleaseCapture( &capture );
	/** Close the window **/
    cvDestroyWindow( "Raw" );
   
}


int main()
{
 	
	backgroundSubtraction();

    return 0;

}
