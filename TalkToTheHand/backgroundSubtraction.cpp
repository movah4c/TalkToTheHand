#include "backgroundSubtraction.h"	

/** Constructor **/
BackgroundSubtraction::BackgroundSubtraction()	
{
	/** Initializing all the variables **/
    model = 0;
    rawImage = 0;
    yuvImage = 0;
    ImaskCodeBook = 0;
    ImaskCodeBookCC = 0;
    ImaskCodeBook1 = 0;
    nframes = 0;
	/** Setting number of frames to learn Background to 100 **/
    nframesToLearnBG = 100;			
    pause1 = false;
    singlestep = false;
	/** Creating a Codebook Model for background **/
    model = cvCreateBGCodeBookModel();

	/** Set color thresholds to default values **/																		
    model->modMin[0] = 3;
    model->modMin[1] = model->modMin[2] = 3;						 
    model->modMax[0] = 10;
    model->modMax[1] = model->modMax[2] = 10;
    model->cbBounds[0] = model->cbBounds[1] = model->cbBounds[2] = 10;


}

/** Destructor **/
BackgroundSubtraction::~BackgroundSubtraction()
{

}

/** Help **/
void BackgroundSubtraction::help()
{
    std::cout<<"\nLearn background and find foreground using simple average and average difference learning method:\n"
            "\nUSAGE:\nbgfg_codebook [--nframes=300] [movie filename, else from camera]\n"<<std::endl;

}

/** Member function to convert the grayscale image to colored image **/
void BackgroundSubtraction::diff_pix(IplImage *image, IplImage *image2)
{
	/** Number of lines**/
    int nl= image2->height; 
	/** Total number of element per line **/
    int nc= image2->width * image2->nChannels; 
    /** Effective width **/
	int step= image2->widthStep;

    /** Get the pointer to the image buffer**/
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

/** Member function to subtract background **/
void BackgroundSubtraction::getSubtractedBackground(IplImage *rawImage)
{
	
    if( !pause1 )
        ++nframes;

    if( singlestep )
        pause = true;

    /** For first iteration **/
    if( nframes == 1 )
    {
        std::cout<<"I am here"<<std::endl;
        /** Codebook method allocation  **/
        yuvImage = cvCloneImage(rawImage);
        ImaskCodeBook = cvCreateImage( cvGetSize(rawImage), IPL_DEPTH_8U, 1 );
        ImaskCodeBookCC = cvCreateImage( cvGetSize(rawImage), IPL_DEPTH_8U, 1 );
        cvSet(ImaskCodeBook,cvScalar(255));
    }

        /** YUV For codebook method  **/
        cvCvtColor( rawImage, yuvImage, CV_BGR2YCrCb );
        
		/** This is where we build our background model  **/
		
		/** Find the foreground if any   **/
        if( nframes-1 >= nframesToLearnBG  )
        {
            /** Find foreground by codebook method  **/
            cvBGCodeBookDiff( model, yuvImage, ImaskCodeBook );
            
			/** This part just to visualize bounding boxes and centers if desired  **/
            cvCopy(ImaskCodeBook,ImaskCodeBookCC);
            cvSegmentFGMask( ImaskCodeBookCC );
			/** Calling member function to convert the obtained grayscale image to colored image **/
            diff_pix(ImaskCodeBookCC,rawImage);

        }
		/** Update the background model till the specified number of frames **/
        else if( !pause1 && (nframes-1 < nframesToLearnBG)  )
            cvBGCodeBookUpdate( model, yuvImage );
		/** Clear stale **/
		else if( nframes-1 == nframesToLearnBG  )
            cvBGCodeBookClearStale( model, model->t/2 );

        /**  Display the output image **/
        std::cout<<"Showing image"<<std::endl;
        cvShowImage( "Raw", rawImage );
    
}

