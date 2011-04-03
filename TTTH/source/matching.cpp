#include "include/matching.h"
#include "stdlib.h"

MatchGesture::MatchGesture(QWidget *parent) : QWidget(parent)
{


    String cascadeName = "aGest.xml";
    String nestedCascadeName = "../../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    std::cout<<cascadeName<<std::endl;
    scale = 3;
    for(int i=0; i<NO_OF_GESTURES; i++)
        charactersOccurences[i]=0;

    maxTillNow = 0;
    maxIndexTillNow = -1;
    if( !nestedCascade.load( nestedCascadeName ) )
        cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;

    if( !cascade.load( cascadeName ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        cerr << "Usage: facedetect [--cascade=\"<cascade_path>\"]\n"
                "   [--nested-cascade[=\"nested_cascade_path\"]]\n"
                "   [--scale[=<image scale>\n"
                "   [filename|camera_index]\n" ;
        // return -1;
    }


}

MatchGesture::~MatchGesture()
{

}

IplImage* MatchGesture::getMatch(IplImage *iplImage)
{

    frame = iplImage;

    if( iplImage->origin == IPL_ORIGIN_TL )
        frame.copyTo( frameCopy );
    else
        flip( frame, frameCopy, 0 );

    detectAndDraw( frameCopy, cascade, nestedCascade, scale );

    IplImage tempImage = frameCopy;
    iplImage = frameCopy;


}

void MatchGesture::detectAndDraw(Mat &img, CascadeClassifier &cascade, CascadeClassifier &nestedCascade, double scale)
{
    //cout<<"A Detected"<<endl;
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
                                      CV_RGB(255,0,255)
                                    };

    Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );

    cvtColor( img, gray, CV_BGR2GRAY );
    cv::resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

    t = (double)cvGetTickCount();
    cascade.detectMultiScale( smallImg, faces,
                              1.1, 2, 0
                              //|CV_HAAR_FIND_BIGGEST_OBJECT
                              //|CV_HAAR_DO_ROUGH_SEARCH
                              |CV_HAAR_SCALE_IMAGE
                              ,
                              Size(30, 30) );
    t = (double)cvGetTickCount() - t;
    // printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
    for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
    {
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        nestedObjects.clear();
        Point center;
        center.x = 0;
        center.y = 0;
        Scalar color = colors[i%8];
        int radius;
        center.x = cvRound((r->x + r->width*0.5)*scale);
        center.y = cvRound((r->y + r->height*0.5)*scale);
        radius = cvRound((r->width + r->height)*0.25*scale);
        if(center.x != 0 || center.y != 0)
        {
            matchedCharacter = 'A';
            int tempIndex = (int)matchedCharacter-48;
            charactersOccurences[tempIndex]=charactersOccurences[tempIndex]+1;
            if(maxTillNow<charactersOccurences[tempIndex])
            {
                maxTillNow = charactersOccurences[tempIndex];
                maxIndexTillNow = tempIndex;
                std::cout<<"Max Index Till now - "<<maxIndexTillNow<<std::endl;
            }

             //cout<<"A Detected"<<endl;
             // system("espeak < speak.txt");
             //emit sendForDisplay('A');
       }

        circle( img, center, radius, color, 3, 8, 0 );
        if( nestedCascade.empty() )
            continue;

        std::cout<<"First circle command"<<std::endl;
        smallImgROI = smallImg(*r);
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
                                        1.1, 2, 0
                                        //|CV_HAAR_FIND_BIGGEST_OBJECT
                                        //|CV_HAAR_DO_ROUGH_SEARCH
                                        //|CV_HAAR_DO_CANNY_PRUNING
                                        |CV_HAAR_SCALE_IMAGE
                                        ,
                                        Size(30, 30) );
        for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
        {
            center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
            center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
            radius = cvRound((nr->width + nr->height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
            std::cout<<"Enter circle drawing - "<<center.x<<"\t"<<center.y<<std::endl;
        }
    }



}



void MatchGesture::getProbableCharacter()
{
    if(maxIndexTillNow != -1 )
    {
        matchedCharacter = (char)(maxIndexTillNow+48);
        //std::cout<<"Emitting - "<<matchedCharacter<<std::endl;
        emit sendForDisplay(matchedCharacter);
    }
    else
    {
        //std::cout<<"Emitting dash."<<std::endl;
        emit sendForDisplay('-');
    }

    for(int i=0; i<NO_OF_GESTURES; i++)
        charactersOccurences[i]=0;

    maxTillNow = 0;
    maxIndexTillNow = -1;
    //matchedCharacter = '-';
}
