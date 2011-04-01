#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "openCVWidget.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>




/**
 * An Enum.
 * These enum values show the system modes in which the application
 * is being operated.
 */
enum
{
    WEBCAM=0, /**< enum value WEBCAM for webcam mode. */
    VIDEOFILE,/**< enum value VIDEOFILE for stored video mode. */
    IMAGEFILE /**< enum value IMAGEFILE for image mode. */
};

/**
 * An Enum.
 * These enum values show the view modes in which the application
 * is being operated.
 */
enum
{
    NORMALVIEW = 0,  /**< enum value NORMAL for webcam view. */
    BACKGROUNDSUB,   /**< enum value BACKGROUNDSUB for bgsubtraction view. */
    HANDDETECT       /**< enum value HANDDETECT for hand detection view. */
};


/**
 * Camera Widget class.
 * This class is the main component of the main window and is responsible for
 * presenting every output to the user based on the input he has provided.
 * This class integrates all modules such as background subtraction, hand
 * detection matching and opencv widget. It updates the view on the main
 * window every few seconds. All system states are handled by this class.
 */

class CameraWidget : public QWidget
{
    Q_OBJECT
private:
    /**
     * A private QOpenCVWidget pointer.
     * This is the widget pointer which is passed the opencv frames and
     * it displays it into the Qt format in a label attached to it.
     */
    OpenCVWidget *cvwidget;

    /**
     * A private CvCapture pointer.
     * This capture mode receives the pointer from the mainwindow and
     * is used to capture further frames from the webcam for processing.
     */
    CvCapture *camera;

    /**
     * A private integer variable.
     * This stores the system view state for this class.
     */
    int viewType;

    /**
     * A private integer variable.
     * This stores the operational mode of the system.
     */
    int operationalMode;

public slots:

    /**
     * A public Qt slot which recieves integer parameter.
     * This slot slot captures the signal emitted from the main
     * window when user requests for a change in view type.
     * @param type an integer to receive changed view type.
     */
    void viewTypeChange(int type);

    /** A public Qt Slot which recieves operational mode.
     *  @param type an integer denoting the input mode of user
     *  @param filename a QString type denoting the input filename
     */
    void operationalModeChange(int mode, QString filename);
public:
    /**
     * Class constructor.
     * This constructor initializes the camera variable for capturing.
     * All the connections to the matching module, background subtraction
     * module and hand detection module are also made in this. The layout
     * is initialzed and a fixed sized frame is made for the images to be
     * displayed.
     * @param cam a CvCapture pointer to receive initialized openCV camera.
     * @param parent a pointer to the main window denoting it as parent.
     */
    CameraWidget(CvCapture *cam, QWidget *parent=0);




protected:
    /**
     * A Private callback function.
     * This is a timer callback function which is called every 0.1
     * seconds to update the view received from the camera. It is this
     * function which also receives the updated output from other
     * modules also.
     */
    void timerEvent(QTimerEvent*);
};


#endif // CAMERAWIDGET_H
