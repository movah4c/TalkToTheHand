#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <iostream>
#include <cstdlib>
#include "cameraWidget.h"
#include "audio.h"
#include "settings.h"



QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
class QLabel;
class QLineEdit;
class QVBoxLayout;
class QSlider;
QT_END_NAMESPACE

/**
 *  MainWindow class.
 *  This class manages the whole application interface and its interaction
 *  with the user. It has signals and slots to connect and receive feedbacks
 *  from the backend of the application. This class creates the toolbars,
 *  menus, status bar, etc, for the application and initializes their callback
 *  functions. This class also acts as the aggregation of all other modules of
 *  the application.
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * A Constructor.
     * The constructor initializes the User Interface of the application
     * by creating the toolbars, actions, statusbar and menus. Their co-
     * rresponding callback slots are also initialized. The initial starting
     * states of the application are also initialized. The openCV camera
     * capture is initialized so that images could be captured from camera.
     * The layout of the application is created and imposed on the window.
     * Basic connections to backend modules are also done in the constructor.
     */
    MainWindow();

signals:

    /** A Qt Signal taking view type (integer) as input.
     *  This signal is emitted whenever the user clicks on any of the
     *  view change buttons to see the other stages of the image
     *  processing on the input provided.
     *  @param type an integer denoting the view type mode of system.
     */
    void ViewTypeChange(int type);

    /** A Qt Signal emitted when user tries to provide input from file.
     *  @param type an integer denoting the input mode of user.
     *  @param filename a QString type denoting the input filename.
     */
    void operationalModeChange(int type, QString filename);

    /** A Qt Signal emitted when user presses play/stop button.
     *  @param state an integer denoting the running state of the system.
     */
    void changeRunningState(int state);

protected:
    /**
     * A normal member function taking one argument.
     * This function is called when the application closes. It is res-
     * ponsible for closing all the files and remove backend connections
     * before closing the application.
     * @param event a QCloseEvent pointer used to refer when closing app.
     */
    void closeEvent(QCloseEvent *event);

public slots:
    /**
     * A Qt slot callback function taking a character as argument.
     * This slot receives the signal from matching module whenever a
     * character is matched and is updated in the main interface.
     * @param c a character type which is the recognized character of that slot.
     */
    void displayRecognizedAlphabet(char c);

private slots:
    /**
     * A normal Qt slot which is called when help tab is clicked.
     */
    void about();
    /**
     * A normal Qt slot which is called when user tries to give
     * image as the input file.
     */
    void openImage();
    /**
     * A normal Qt slot which is called when user gives video as
     * the input file for the system.
     */
    void openVideo();
    /**
     * A normal Qt slot which is called when user is ready to start.
     * recognition of his gesture and clicks on the play button.
     */
    void startRecognition();
    /**
     * A normal Qt slot which is called when user is wants to stop
     * recognition of his gesture and clicks on the stop button.
     */
    void stopRecognition();
    /**
     * A normal Qt slot which is called when mute button is pressed.
     */
    void mute();
    /**
     * A normal Qt slot which is called when user increases or
     * decreases the volume.
     */
    void volume();
    /**
     * A normal Qt slot to change view to normal mode.
     */
    void normalView();
    /**
     * A normal Qt slot to change view to background subtraction.
     */
    void backroundSubView();

    /**
     * A normal Qt slot to change view ot hand detection view.
     */
    void handDetectView();

    /**
     * A normal Qt slot to options for the software.
     */
    void options();

    /**
     * A normal Qt slot to display trainer tool for the software.
     */
    void trainerTool();

    /**
     * A normal Qt slot to change settings for the software.
     */
    void applySettings();



private:
    /**
     * A Function to create Actions which are being used in the
     * application and initialization of the connections pertaining
     * to those actions.
     */
    void createActions();
    /**
     * A Private Function.
     * Creates the menus used in the user interface.
     */
    void createMenus();
    /**
     * A Private Function.
     * Creates toolbars for the user interface and initializes their
     * actions which are called when tool buttons are clicked.
     */
    void createToolBars();
    /**
     * A Private Function.
     * This creates the status bar for the application and initializes
     * the data to be shown in the status bar.
     */
    void createStatusBar();

    /**
     * A Private callback function.
     * This is a timer callback function which is called every N
     * seconds. In every three seconds, it calls the matching module
     * for the matched symbol and gets its update.
     */
    void timerEvent(QTimerEvent*);

    /**
     * A private variable.
     * The value in the variable shows the state in which system is
     * operating. Three modes are Video Input mode, Image Input mode
     * and Normal Webcam mode.
     */
    int mode;
    /**
     * A private PlayAudio pointer.
     * This pointer is used to link the audio output module to the
     * interface and the characters/words to be spoken and send to
     * the member function of this class so that it can be commu-
     * nicated to the hardware.
     */
    PlayAudio *audioList;
    /**
     * A private CameraWidget variable pointer.
     * This pointer is used to access the CameraWidget in the main
     * interface. This pointer helps to send information to the main
     * backend module.
     */
    CameraWidget *mainCameraWidget;

    Settings *applicationSettings;

    /**
     * A private QMenu variable pointer.
     * This variable stores the file menu of the interface.
     */
    QMenu *fileMenu;
    /**
     * A private QMenu variable pointer.
     * This variable stores the view menu of the application.
     */
    QMenu *viewMenu;
    /**
     * A private QMenu variable pointer.
     * This variable stores the help menu of the application.
     */
    QMenu *helpMenu;

    /**
     * A priavte QMenu variable pointer.
     * This variable creates the tools menu of the application.
     */
    QMenu *toolMenu;

    /**
     * A private QToolBar variable pointer.
     * This variable stores the file toolbar of the interface.
     */
    QToolBar *fileToolBar;

    /**
     * A private QToolBar variable pointer.
     * This variable stores the view toolbar of the interface.
     */
    QToolBar *viewToolBar;

    /**
     * A private QMenu variable pointer.
     * This variable stores the control Toolbar of the interface.
     */
    QToolBar *controlToolBar;

    /**
     * A private QSlider variable pointer.
     * This slider is used to get changed value of the volume.
     */
    QSlider *volumeSlider;

    /**
     * A private QAction variable pointer.
     * This action is used to change view mode to normal webcam mode.
     */
    QAction *normalViewAct;

    /**
     * A private QAction variable pointer.
     * This action is used change view mode value of the application.
     */
    QAction *backgroundSubViewAct;

    /**
     * A private QAction variable pointer.
     * This action is used to change view mode to hand detection.
     */
    QAction *handDetectViewAct;

    /**
     * A private QAction variable pointer.
     * This action starts the gesture recognition activity.
     */
    QAction *startAct;

    /**
     * A private QAction variable pointer.
     * This action stops the gesture recognition activity.
     */
    QAction *stopAct;

    /**
     * A private QAction variable pointer.
     * This action mutes the volume.
     */
    QAction *muteAct;

    /**
     * A private QAction variable pointer.
     * This action triggers the change in volume.
     */
    QAction *volumeAct;

    /**
     * A private QAction variable pointer.
     * This action opens a file dialog window for opening image.
     */
    QAction *openImageAct;

    /**
     * A private QAction variable pointer.
     * This action opens a file dialog window for opening video.
     */
    QAction *openVideoAct;

    /**
     * A private QAction variable pointer.
     * This action is triggered when about Application is clicked.
     */
    QAction *aboutAct;

    /**
     * A private QAction variable pointer.
     * This action is triggered when about Qt is clicked.
     */
    QAction *aboutQtAct;

    /**
     * A private QAction variable pointer.
     * This is action is triggered when application is going to close.
     */
    QAction *exitAct;

    /**
     * A private QAction variable pointer.
     * This action is triggered when options is clicked from the tools menu.
     */
    QAction *optionsAct;

    /**
     * A private QAction variable pointer.
     * This action is triggered when user clicks on training option from tools menu.
     */
    QAction *trainerAct;


    /**
     * A private QLineEdit variable pointer.
     * This is the text box which is shown at the bottom page of the
     * application. This stores all the characters which have been
     * recorded till now and shows it on the interface.
     */
    QLineEdit *outputText;
};

#endif // MAINWINDOW_H
