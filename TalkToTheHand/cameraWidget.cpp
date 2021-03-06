#include "cameraWidget.h"
#include <iostream>


/** Constructor */
CameraWidget::CameraWidget(CvCapture *cam, QWidget *parent) : QWidget(parent)
{
    /** Initializing values to be used by this class */
    camera = cam;
    QVBoxLayout *layout = new QVBoxLayout;

    cvwidget = new OpenCVWidget(this);

    /** Add the widget to the layout which is then added to the window. */
    layout->addWidget(cvwidget);
    setLayout(layout);

    /** Resize the output to a particular size */
    resize(500, 400);

    /** Initialize the timer for 0.1 seconds update*/
    startTimer(010);

    /** Set operational mode of the application */
    viewType = NORMALVIEW;
    operationalMode = WEBCAM;

 }

/** Update the widget every 0.1 second according to the timer */
void CameraWidget::timerEvent(QTimerEvent*)
{
    IplImage *image=cvQueryFrame(camera);
    cvwidget->putImage(image);
}

/** Changin view type of the application */
void CameraWidget::viewTypeChange(int type)
{
    viewType = type;
}

/** Change operational mode of the application */
void CameraWidget::operationalModeChange(int mode, QString filename)
{
    operationalMode = mode;
}

