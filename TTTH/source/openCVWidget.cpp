#include "include/openCVWidget.h"


/** Constructor */
OpenCVWidget::OpenCVWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout;
    imagelabel = new QLabel;
    QImage dummy(100,100,QImage::Format_RGB32);
    image = dummy;
    layout->addWidget(imagelabel);
    for (int x = 0; x < 100; x ++)
    {
        for (int y =0; y < 100; y++)
        {
            image.setPixel(x,y,qRgb(x, y, y));
        }
    }

    imagelabel->setPixmap(QPixmap::fromImage(image));
    setLayout(layout);
}

/** Destructor */
OpenCVWidget::~OpenCVWidget(void)
{

}

/** Putting image to the QLabel */
void OpenCVWidget::putImage(IplImage *cvimage)
{
    int h=cvimage->height;
    int w=cvimage->width;
    int channels = cvimage->nChannels;
    QImage temp(w, h, QImage::Format_RGB32);
    image = temp;
    char *data = cvimage->imageData;
    for(int y=0; y<h; y++, data +=cvimage->widthStep)
    {
        for(int x=0; x<w; x++)
        {
            char r, g, b, a=0;
            if(channels == 1)
            {
                r=data[x*channels];
                g=data[x*channels];
                b=data[x*channels];
            }
            else if (channels == 3 || channels == 4)
            {
                r = data[x * channels + 2];
                g = data[x * channels + 1];
                b = data[x * channels];
            }

            if (channels == 4)
            {
                a = data[x * channels + 3];
                image.setPixel(x, y, qRgba(r, g, b, a));
            }
            else
            {
                image.setPixel(x, y, qRgb(r, g, b));
            }
        }
    }

     image=image.scaledToHeight(540);
     imagelabel->setPixmap(QPixmap::fromImage(image));

}


/** Converting QImage to IplImage */
IplImage* OpenCVWidget::QImage2IplImage(QImage *qimg)
{
    IplImage *imgHeader = cvCreateImageHeader( cvSize(qimg->width(), qimg->width()), IPL_DEPTH_8U, 4);
    imgHeader->imageData = (char*) qimg->bits();

    uchar* newdata = (uchar*) malloc(sizeof(uchar) * qimg->byteCount());
    memcpy(newdata, qimg->bits(), qimg->byteCount());
    imgHeader->imageData = (char*) newdata;

    return imgHeader;
}

/** Converting IplImage to QImage */
QImage*  OpenCVWidget::IplImage2QImage(IplImage *iplImg)
{
    int h = iplImg->height;
    int w = iplImg->width;
    int channels = iplImg->nChannels;
    QImage *qimg = new QImage(w, h, QImage::Format_ARGB32);
    char *data = iplImg->imageData;

    for (int y = 0; y < h; y++, data += iplImg->widthStep)
    {
        for (int x = 0; x < w; x++)
        {
            char r, g, b, a = 0;
            if (channels == 1)
            {
                r = data[x * channels];
                g = data[x * channels];
                b = data[x * channels];
            }
            else if (channels == 3 || channels == 4)
            {
                r = data[x * channels + 2];
                g = data[x * channels + 1];
                b = data[x * channels];
            }

            if (channels == 4)
            {
                a = data[x * channels + 3];
                qimg->setPixel(x, y, qRgba(r, g, b, a));
            }
            else
            {
                qimg->setPixel(x, y, qRgb(r, g, b));
            }
        }
    }
    return qimg;

}
