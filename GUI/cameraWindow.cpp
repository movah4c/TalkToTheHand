
#include "cameraWindow.h"

CameraWindow::CameraWindow(CvCapture *cam, QWidget *parent) : QWidget(parent)
{
    camera = cam;
    QVBoxLayout *layout = new QVBoxLayout;
    cvwidget = new QOpenCVWidget(this);
    layout->addWidget(cvwidget);
    setLayout(layout);
    resize(500, 400);

    startTimer(100);  // 0.1-second timer
 }

void CameraWindow::timerEvent(QTimerEvent*)
{
    IplImage *image=cvQueryFrame(camera);
    cvwidget->putImage(image);
}


