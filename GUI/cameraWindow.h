#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include "QOpenCVWidget.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>


class CameraWindow : public QWidget
{
    Q_OBJECT
    private:
        QOpenCVWidget *cvwidget;
        CvCapture *camera;

    public:
        CameraWindow(CvCapture *cam, QWidget *parent=0);

    protected:
        void timerEvent(QTimerEvent*);


};



#endif // CAMERAWINDOW_H
