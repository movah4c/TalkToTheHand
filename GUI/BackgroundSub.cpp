
#include "cvaux.h"
#include "cxmisc.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

CvRect cvMakeRect(int x1,int y1,int x2,int y2)
{
return cvRect(x1,y1,abs(x2-x1), abs(y2-y1));
}

int main(int argc, char** argv)
{
    CvBGCodeBookModel* model = 0;
    IplImage* rawImage = 0, *yuvImage = 0, *temp=0, *dst=0; //yuvImage is for codebook method
    IplImage *ImaskCodeBook = 0,*ImaskCodeBookCC = 0, *tempImg=0,*topleft=0,*topright=0,*bottomleft=0,*bottomright=0;
    CvCapture* capture = cvCaptureFromCAM(0);

    CvMemStorage *storage = cvCreateMemStorage(0);

    int c, nframes = 0;
    int nframesToLearnBG = 30;
    int xc=0, yc=0, flag;

    model = cvCreateBGCodeBookModel();

    //Set color thresholds to default values
    model->modMin[0] = 3;
    model->modMin[1] = model->modMin[2] = 3;
    model->modMax[0] = 10;
    model->modMax[1] = model->modMax[2] = 10;
    model->cbBounds[0] = model->cbBounds[1] = model->cbBounds[2] = 10;



    if( !capture )
    {
        printf( "Can not initialize video capturing\n\n" );
        exit(1);
    }

    //MAIN PROCESSING LOOP:
    for(;;)
    {
            rawImage = cvQueryFrame( capture );
            ++nframes;
            if(!rawImage)
                break;

        //First time:
        if( nframes == 1 && rawImage )
        {
            // CODEBOOK METHOD ALLOCATION
            yuvImage = cvCloneImage(rawImage);
            ImaskCodeBook = cvCreateImage( cvGetSize(rawImage), IPL_DEPTH_8U, 1 );
            ImaskCodeBookCC = cvCreateImage( cvGetSize(rawImage), IPL_DEPTH_8U, 1 );
            temp = cvCreateImage( cvGetSize(rawImage), IPL_DEPTH_8U, 1 );
            dst = cvCreateImage( cvGetSize(rawImage), IPL_DEPTH_8U, 1 );
            cvZero(temp);
            cvSet(ImaskCodeBook,cvScalar(255));
        }

        // If we've got an rawImage and are good to go:
        if( rawImage )
        {
            cvCvtColor( rawImage, yuvImage, CV_BGR2YCrCb );//YUV For codebook method
            //This is where we build our background model
            if(nframes-1 < nframesToLearnBG  )
                cvBGCodeBookUpdate( model, yuvImage );

            if( nframes-1 == nframesToLearnBG  )
                cvBGCodeBookClearStale( model, model->t/2 );

            //Find the foreground if any
            if( nframes-1 >= nframesToLearnBG  )
            {
                // Find foreground by codebook method
              flag=0;
                cvBGCodeBookDiff( model, yuvImage, ImaskCodeBook );
                // This part just to visualize bounding boxes and centers if desired
                cvCopy(ImaskCodeBook,ImaskCodeBookCC);
                cvSegmentFGMask( ImaskCodeBookCC );

                tempImg=cvCloneImage(ImaskCodeBookCC);

                topleft=cvCloneImage(ImaskCodeBookCC);
                topright=cvCloneImage(ImaskCodeBookCC);
                bottomleft=cvCloneImage(ImaskCodeBookCC);
                bottomright=cvCloneImage(ImaskCodeBookCC);

                cvCmp(temp, ImaskCodeBookCC, dst, CV_CMP_EQ);

                for(int i=0;i<dst->height;i++)
                  for(int j=0;j<dst->width;j++)
                    {
                      if(cvGet2D(dst, i, j).val[0]==0x00)
                        {
                        flag = 1;
                        break;
                        }
                    }



                if(flag)
                {
                  CvRect box = cvBoundingRect(tempImg, 1);

                  CvMoments moments;

                  cvMoments(ImaskCodeBookCC, &moments, 1);

                  xc = (int)(moments.m10/moments.m00);
                  yc = (int)(moments.m01/moments.m00);

                  cvRectangleR(ImaskCodeBookCC,box, cvScalarAll(255), 1, 8, 0);

                  cvLine(ImaskCodeBookCC, cvPoint(0,yc), cvPoint(ImaskCodeBookCC->width,yc), cvScalarAll(255), 1, 8, 0);
                  cvLine(ImaskCodeBookCC, cvPoint(xc,0), cvPoint(xc,ImaskCodeBookCC->height), cvScalarAll(255), 1, 8, 0);

//                cvSetImageROI(topleft,cvRect(box.x,box.y,abs(box.x-xc),abs(box.y-yc)));
//                cvSetImageROI(topright,cvRect(xc,box.y,abs((box.x+box.width)-xc),abs(yc-box.y)));
//                cvSetImageROI(bottomleft,cvRect(box.x,yc,abs(xc-box.x),abs(yc-box.height)));
//                cvSetImageROI(bottomright,cvRect(xc,yc,abs(box.x-xc),abs(box.y-yc)));

                  cvSetImageROI(topleft,cvMakeRect(0,0,xc,yc));
                  cvSetImageROI(topright,cvMakeRect(xc,0,ImaskCodeBookCC->width,yc));
                  cvSetImageROI(bottomleft,cvMakeRect(0,yc,xc,ImaskCodeBookCC->height));
                  cvSetImageROI(bottomright,cvMakeRect(xc,yc,ImaskCodeBookCC->width,ImaskCodeBookCC->height));
                }


                cvShowImage("arbit", ImaskCodeBookCC);
                cvShowImage("tl", topleft);
                cvShowImage("tr", topright);
                cvShowImage("bl", bottomleft);
                cvShowImage("br", bottomright);


            }

        }

        // User input:
        c = cvWaitKey(10)&0xFF;
        c = tolower(c);
        // End processing on ESC, q or Q
        if(c == 27 || c == 'q')
            break;
    }

    cvReleaseCapture( &capture );
    cvReleaseImage(&rawImage);
    cvReleaseImage(&yuvImage);
    cvReleaseImage(&ImaskCodeBook);
    cvReleaseImage(&ImaskCodeBookCC);
    cvReleaseMemStorage(&storage);
    return 0;
}
