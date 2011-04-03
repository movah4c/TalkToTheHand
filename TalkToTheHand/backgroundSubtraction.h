#ifndef BACKGROUNDSUBTRACTION_H
#define BACKGROUNDSUBTRACTION_H


#include <opencv/cv.h>
#include "opencv/cvaux.h"
#include "opencv/cxmisc.h"
#include "opencv/highgui.h"
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <ctype.h>

using namespace cv;

const int NCHANNELS = 3;

class BackgroundSubtraction
{

private:
    CvBGCodeBookModel* model;

    IplImage* rawImage;
    /** yuvImage is for codebook method **/
    IplImage *yuvImage;
    IplImage *ImaskCodeBook;
    IplImage *ImaskCodeBookCC;
    IplImage *ImaskCodeBook1;
    int c;
    int n;
    int nframes;
    int nframesToLearnBG;
    bool pause1;
    bool singlestep;


    /** This sets what channels should be adjusted for background bounds **/
    bool ch[NCHANNELS];

    void help(void);
    void diff_pix(IplImage* image,IplImage* image2);

public:
	/** Constructor **/
    BackgroundSubtraction();
	/** Destructor **/
    ~BackgroundSubtraction();
	/** Background subtraction **/
    void getSubtractedBackground(IplImage* rawData);


};





#endif // BACKGROUNDSUBTRACTION_H
