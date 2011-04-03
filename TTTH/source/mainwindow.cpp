
#include <QtGui>
#include "include/mainwindow.h"

MainWindow::MainWindow()
{

    /** Call these functions to initalize actions, menus and toolbars. */
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    //viewType = NORMALVIEW;
    //operationalMode = WEBCAM;
    /** Create audio list */
    audioList = new PlayAudio(this);
    mode = WEBCAM;

    /** Initialize opencv camera */
    CvCapture *camera = cvCreateCameraCapture(0);
    assert(camera);
    IplImage *image=cvQueryFrame(camera);
    assert(image);
    mainCameraWidget = new CameraWidget(camera, this);

    /** Initialize text box */
    outputText = new QLineEdit(tr(""));
    outputText->setReadOnly(true);

    applicationSettings = new Settings();

    /** Creating main layout of the application */
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mainCameraWidget);
    mainLayout->addWidget(outputText);
    QWidget *widget = new QWidget();
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
    this->setMouseTracking(true);

    /** Starting time to take update from the matching module */
    startTimer(3000);

    /** Connecting the main window with the camera widget and with the matching module */
    connect(this, SIGNAL(ViewTypeChange(int)), mainCameraWidget, SLOT(viewTypeChange(int)));
    connect(this, SIGNAL(operationalModeChange(int,QString)), mainCameraWidget, SLOT(operationalModeChange(int,QString)));
    connect(mainCameraWidget->matchGesture, SIGNAL(sendForDisplay(char)), this, SLOT(displayRecognizedAlphabet(char)));
    connect(this, SIGNAL(changeRunningState(int)), mainCameraWidget, SLOT(changeRunningState(int)));
    connect(applicationSettings->applyButton, SIGNAL(clicked()), this, SLOT(applySettings()));
    connect(applicationSettings->cancelButton, SIGNAL(clicked()), this, SLOT(options()));

}

/** Timer callback function */
void MainWindow::timerEvent(QTimerEvent *)
{

    if(mainCameraWidget->runningState == PLAY)
    {
        std::cout<<"Requesting matched character"<<std::endl;
        mainCameraWidget->matchGesture->getProbableCharacter();
    }

}

/** Close event */
void MainWindow::closeEvent(QCloseEvent *event)
{
    std::cout<<"Closing application..."<<std::endl;
}



/** About the application */
void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Talk To The Hand</b> is a hand gesture recongition  "
               "application(ASL) developed in Qt environment and using OpenCV "
               "for image processing."));
}

/** Create actions required in the application */
void MainWindow::createActions()
{


    /** Create actions for switching to normal view */
    normalViewAct = new QAction(QIcon(":/resource/images/eye_icon&32.png"), tr("Webcam view"), this);
    normalViewAct->setStatusTip("Open normal view window");
    connect(normalViewAct, SIGNAL(triggered()), this, SLOT(normalView()));

    /** Create actions for switching to background subtraction view */
    backgroundSubViewAct = new QAction(QIcon(":/resource/images/clipboard_copy_icon&32.png"), tr("Background Subtracted View"), this);
    backgroundSubViewAct->setStatusTip("Open  background subtracted view");
    connect(backgroundSubViewAct, SIGNAL(triggered()), this, SLOT(backroundSubView()));

    /** Create actions for switching to hand detection view */
    handDetectViewAct = new QAction(QIcon(":/resource/images/hand_1_icon&32.png"), tr("Hand Detection View"), this);
    handDetectViewAct->setStatusTip("Open hand detection view");
    connect(handDetectViewAct, SIGNAL(triggered()), this, SLOT(handDetectView()));

    /** Create action to open image file as input */
    openImageAct = new QAction(QIcon(":/resource/images/folder_icon&32.png"), tr("Open Image"), this);
    openImageAct->setStatusTip("Open image as the input gesture");
    connect(openImageAct, SIGNAL(triggered()), this, SLOT(openImage()));

    /** Create action to open video file as input */
    openVideoAct = new QAction(QIcon(":/resource/images/folder_open_icon&32.png"), tr("Open Video"), this);
    openVideoAct->setStatusTip("Open video as the input gesture");
    connect(openVideoAct, SIGNAL(triggered()), this, SLOT(openImage()));

    /** Create action to start gesture recognition */
    startAct = new QAction(QIcon(":/resource/images/playback_play_icon&32.png"), tr("Start recognition"), this);
    startAct->setStatusTip("Start gesture recongition");
    connect(startAct, SIGNAL(triggered()), this, SLOT(startRecognition()));

    /** Create action to stop gesture recognition */
    stopAct = new QAction(QIcon(":/resource/images/playback_stop_icon&32.png"), tr("Stop recognition"), this);
    stopAct->setStatusTip("Stop gesture recongition");
    connect(stopAct, SIGNAL(triggered()), this, SLOT(stopRecognition()));

    /** Create mute action */
    muteAct = new QAction(QIcon(":/resource/images/sound_mute_icon&32.png"), tr("Mute"), this);
    muteAct->setStatusTip("Mute");
    connect(muteAct, SIGNAL(triggered()), this, SLOT(mute()));

    /** Create volume change action */
    volumeAct = new QAction(QIcon(":/resource/images/sound_high_icon&32.png"), tr("Adjust volume"), this);
    volumeAct->setStatusTip("Adjust volume");
    connect(volumeAct, SIGNAL(triggered()), this, SLOT(volume()));

    /** Create action to view about help for application */
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    /** Create action to change about Qt help for application */
    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    /** Create exit action for the application */
    exitAct = new QAction(QIcon(":/resource/images/on-off_icon&32.png"), tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    /** Create trainer action for the application */
    trainerAct = new QAction(tr("Trainer"), this);
    trainerAct->setStatusTip(tr("Train software for gestures"));
    connect(trainerAct, SIGNAL(triggered()), this, SLOT(trainerTool()));

    optionsAct = new QAction(tr("Options"), this);
    optionsAct->setStatusTip(tr("Settings for the application"));
    connect(optionsAct, SIGNAL(triggered()), this, SLOT(options()));

}

/** Create menus */
void MainWindow::createMenus()
{

    /** Creating file menu bar */
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openImageAct);
    fileMenu->addAction(openVideoAct);
    fileMenu->addAction(exitAct);
    menuBar()->addSeparator();

    /** Creating file view bar */
    viewMenu=menuBar()->addMenu(tr("Views"));
    viewMenu->addAction(normalViewAct);
    viewMenu->addAction(backgroundSubViewAct);
    viewMenu->addAction(handDetectViewAct);
    menuBar()->addSeparator();

    /** Creating tools menu */
    toolMenu = menuBar()->addMenu(tr("&Tools"));
    toolMenu->addAction(trainerAct);
    toolMenu->addAction(optionsAct);
    menuBar()->addSeparator();

    /** Creating file help bar */
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

/** Creating tool bars */
void MainWindow::createToolBars()
{
    /** Creating volume slider on the interface */
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setMaximum(100);
    volumeSlider->setFixedWidth(100);
    volumeSlider->addAction(volumeAct);
    volumeSlider->setValue(50);
    connect(volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(volume()));


    /** Creating file toolbar */
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openVideoAct);
    fileToolBar->addAction(openImageAct);
    fileToolBar->addAction(exitAct);

    /** Creating tool bar for changing views */
    viewToolBar = addToolBar(tr("Views"));
    viewToolBar->addAction(normalViewAct);
    viewToolBar->addAction(backgroundSubViewAct);
    viewToolBar->addAction(handDetectViewAct);

    /** Creating toolbar for controlling the recognition timers and volumes */
    controlToolBar = addToolBar(tr("Recognition Controls"));
    controlToolBar->addAction(startAct);
    controlToolBar->addAction(stopAct);
    controlToolBar->addAction(muteAct);
    controlToolBar->addAction(volumeAct);
    controlToolBar->addWidget(volumeSlider);

}

/** Creating status bar for the application */
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


void MainWindow::openImage()
{
    /** Open file dialog box for opening the image */
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"), "/home", tr("JPEG Files (*.jpg *.jpeg *.jpe);;Windows bitmaps(*.BMP *.DIB);;Portable Network Graphics(*.png);;Portable Image Format(*.pbm *.pgm *ppm"));
    if (!fileName.isEmpty())
    {
        std::cout<<"Opening file - "<<fileName.toStdString()<<std::endl;
        emit operationalModeChange(IMAGEFILE, fileName);
    }

}

void MainWindow::openVideo()
{
    /** Open file dialog box for opening the videos */
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), ".", tr("Images(*.avi)"));
    if (!fileName.isEmpty())
    {
        std::cout<<"Opening file - "<<fileName.toStdString()<<std::endl;
        emit operationalModeChange(VIDEOFILE, fileName);
    }


}

/** Switch to normal view */
void MainWindow::normalView()
{

    std::cout<<"Showing normal view"<<endl;
    emit ViewTypeChange(NORMALVIEW);

}

/** Switch to background subtracted view */
void MainWindow::backroundSubView()
{
    std::cout<<"Background Subtracted View"<<endl;
    audioList->addToPlayList("test1.mp3");
    emit ViewTypeChange(BACKGROUNDSUB);

}

/** Switch to hand detect view */
void MainWindow::handDetectView()
{
    std::cout<<"Hand Detection View  = "<<HANDDETECT<<endl;
    //viewType = HANDDETECT;
    emit ViewTypeChange(HANDDETECT);

}

/** Start gesture recognition */
void MainWindow::startRecognition()
{
    std::cout<<"Starting gesture recognition"<<std::endl;
    outputText->setText("");
    emit changeRunningState(PLAY);

}

/** Stop gesture recognition */
void MainWindow::stopRecognition()
{
    std::cout<<"Stopping gesture recognition"<<std::endl;
    emit changeRunningState(PAUSE);
}

/** Mute the volume */
void MainWindow::mute()
{
    std::cout<<"Mute volume"<<std::endl;
    audioList->changeVolume(0);

}

/** Change volume */
void MainWindow::volume()
{
    std::cout<<"Unmuting"<<std::endl;
    audioList->changeVolume(volumeSlider->value());

}

/** Display matched text */
void MainWindow::displayRecognizedAlphabet(char c)
{
    if(c!='-')
    {
        outputText->setText(outputText->text() + QString(c));
        system("espeak < speak.txt");
    }
}

/** Option slot */
void MainWindow::options()
{
    if(applicationSettings->isActiveWindow())
        applicationSettings->hide();
    else
        applicationSettings->show();
}

/** Trainer slot */
void MainWindow::trainerTool()
{

}

/** Settings slot */
void MainWindow::applySettings()
{
    std::cout<<"Apply button clicked"<<std::endl;
}
