#ifndef OPENCVWIDGET_H
#define OPENCVWIDGET_H

#include <opencv/cv.h>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QImage>


/**
 * OpenCV Widget class
 * This class is used to combine openCV and Qt. The IplImage format
 * of OpenCV is passed onto this class and it converts it into a
 * QImage and tags it to a QLabel so that it can be integrated in
 * the Qt Gui to be shown to the user. It is inherited publicly from
 * the QWidget class.
 */
class OpenCVWidget : public QWidget
{
private:
    /**
     * Pointer to QLabel
     * This QLabel pointer is the label on which the converted
     * image is mapped to. The converted QImage is assigned to
     * this label in the form of QPixmap.
     */
    QLabel *imagelabel;

    /**
     * Pointer to QVBoxLayout
     * This is used to set the label in proper layout.
     */
    QVBoxLayout *layout;

    /**
     * Object of QImage
     * This object is the one in which the IplImage is converted to
     * and this image is then assigned to the label.
     */
    QImage image;

public:

    /**
     * Constructor of OpenCV Widget class
     * This constructor initialzes all the pointer variables of the class
     * and sets the layout.
     * @param parent a pointer to QWidget assigning the parent of this widget
     */
    OpenCVWidget(QWidget *parent = 0);

    /**
     * Destructor
     */
    ~OpenCVWidget(void);

    /**
     * A public function
     * This function is called when IplImage has to be converted into
     * QImage for Qt openCV integration. This function reads pixel by
     * pixel values from the IplImage and assigns it to the QImage.
     * @param cvimage a pointer to IplImage which stores the image
     * currently being used.
     */
    void putImage(IplImage *cvimage);

    /**
     * A public function
     * This function is used to convert QImage to IplImage. Since this
     * widget is used for integration of Qt with openCV. This functionality
     * is included to include both directional compatibility.
     */
    IplImage* QImage2IplImage(QImage *qimg);

    /**
     * A public function
     * This function is reponsible for converting the IplImage to QImage
     * and it mainly takes care of the different IplImage formats and
     * channels.
     */
    QImage* IplImage2QImage(IplImage *iplImg);
};


#endif // OPENCVWIDGET_H
