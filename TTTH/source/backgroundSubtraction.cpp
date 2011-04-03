#include "include/backgroundSubtraction.h"


BackgroundSubtraction::BackgroundSubtraction()
{
    model = 0;
    //NCHANNELS = 3;
    rawImage = 0;
    yuvImage = 0;
    ImaskCodeBook = 0;
    ImaskCodeBookCC = 0;
    ImaskCodeBook1 = 0;
    nframes = 0;
    nframesToLearnBG = 100;
    pause = false;
    singlestep = false;

    model = cvCreateBGCodeBookModel();

    /* Set color thresholds to default values */
    model->modMin[0] = 3;
    model->modMin[1] = model->modMin[2] = 3;
    model->modMax[0] = 10;
    model->modMax[1] = model->modMax[2] = 10;
    model->cbBounds[0] = model->cbBounds[1] = model->cbBounds[2] = 10;


}

BackgroundSubtraction::~BackgroundSubtraction()
{

}


void BackgroundSubtraction::help()
{
    std::cout<<"\nLearn background and find foreground using simple average and average difference learning method:\n"
            "\nUSAGE:\nbgfg_codebook [--nframes=300] [movie filename, else from camera]\n"<<std::endl;

}

void BackgroundSubtraction::diff_pix(IplImage *image, IplImage *image2)
{
    int nl= image2->height; // number of lines
    int nc= image2->width * image2->nChannels; // total number of element per line
    int step= image2->widthStep; // effective width

    // get the pointer to the image buffer

    for (int j = 0; j < nl; j++) {

        uchar* pSrc1 = (uchar*) (image->imageData + j * image->widthStep);
        uchar* pSrc2 = (uchar*) (image2->imageData + j * image2->widthStep);

        for (int k = 0; k < nc; k++) {
            //setting RGB components corresponding to black colored pixels of the gray scale image to zero
            if( pSrc1[k]==0)
            {
                pSrc2[3*k]=0;
                pSrc2[3*k+1]=0;
                pSrc2[3*k+2]=0;
            }

        }

    }


}


void BackgroundSubtraction::getSubtractedBackground(IplImage *rawImage)
{

    if( !pause )
        ++nframes;

    if( singlestep )
        pause = true;

    /* For first iteration */
    if( nframes == 1 && rawImage )
    {
        std::cout<<"I am here"<<std::endl;
        /* CODEBOOK METHOD ALLOCATION  */
        yuvImage = cvCloneImage(rawImage);
        ImaskCodeBook = cvCreateImage( cvGetSize(rawImage), IPL_DEPTH_8U, 1 );
        ImaskCodeBookCC = cvCreateImage( cvGetSize(rawImage), IPL_DEPTH_8U, 1 );
        cvSet(ImaskCodeBook,cvScalar(255));

        //cvNamedWindow( "Raw", 1 );
        // cvNamedWindow( "ForegroundCodeBook",1);
        // cvNamedWindow( "CodeBook_ConnectComp",1);
    }

    /* If we've got an rawImage and are good to go */
    if( rawImage )
    {
        /* YUV For codebook method  */
        cvCvtColor( rawImage, yuvImage, CV_BGR2YCrCb );
        /* This is where we build our background model  */
        //std::cout<<" NFrames - "<<nframes<<" Pause Flag - "<<pause<<std::endl;

        if( !pause && (nframes-1 < nframesToLearnBG)  )
            cvBGCodeBookUpdate( model, yuvImage );

        if( nframes-1 == nframesToLearnBG  )
            cvBGCodeBookClearStale( model, model->t/2 );

        /* Find the foreground if any   */
        if( nframes-1 >= nframesToLearnBG  )
        {
            /* Find foreground by codebook method  */
            cvBGCodeBookDiff( model, yuvImage, ImaskCodeBook );
            /* This part just to visualize bounding boxes and centers if desired  */
            cvCopy(ImaskCodeBook,ImaskCodeBookCC);
            cvSegmentFGMask( ImaskCodeBookCC );

            diff_pix(ImaskCodeBookCC,rawImage);

        }
        /*  Display  */
        //std::cout<<"Showing image"<<std::endl;
        //cvShowImage( "Raw", rawImage );
    }
}

