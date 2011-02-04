#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    readSettings();

    camera = cvCreateCameraCapture(0);
    assert(camera);
    IplImage* image = cvQueryFrame(camera);
    assert(image);
    printf("Image depth=%i\n", image->depth);
    printf("Image nChannels=%i\n", image->nChannels);
    mainLayout = new QGridLayout;

    openCVCameraWindow = new CameraWindow(camera);
    backgroundSubWindow = new CameraWindow(camera);
    matchWindow = new CameraWindow(camera);
    handDetectWindow = new CameraWindow(camera);

    mainLayout->addWidget(openCVCameraWindow, 0, 0);
    mainLayout->addWidget(backgroundSubWindow, 0, 1);
    mainLayout->addWidget(handDetectWindow, 1, 0);
    mainLayout->addWidget(matchWindow, 1, 1);
    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);
    this->setFixedSize(1000, 700);


    //setCentralWidget(openCVCameraWindow);

}


MainWindow::~MainWindow()
{
    cvReleaseCapture(&camera);
}

void MainWindow::closeEvent(QCloseEvent *event)
{

}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Application"),
                       tr("The <b>Application</b> example demonstrates how to "
                          "write modern GUI applications using Qt, with a menu bar, "
                          "toolbars, and a status bar."));
}

void MainWindow::createActions()
{
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's about box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    originalView = new QAction(tr("Original View"), this);
    originalView->setStatusTip(tr("Shows original camera view"));
    connect(originalView, SIGNAL(triggered()), this, SLOT(showOriginalView()));

    backgroundSubstractionView = new QAction(tr("Background Subtraction View"), this);
    backgroundSubstractionView->setStatusTip(tr("This shows the view with background substracted"));
    connect(backgroundSubstractionView, SIGNAL(triggered()), this, SLOT(showBackgroundSubstractionView()));

    handDetectionView = new QAction(tr("Hand Detection View"), this);
    handDetectionView->setStatusTip(tr("This shows the hand detection window"));
    connect(handDetectionView, SIGNAL(triggered()), this, SLOT(showHandDetectionView()));

    matchView = new QAction(tr("Match View"), this);
    matchView->setStatusTip(tr("This show the gesture matched with the current view"));
    connect(matchView, SIGNAL(triggered()), this, SLOT(showMatchView()));



}


void MainWindow::createMenus()
{
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(exitAct);

        viewMenu = menuBar()->addMenu(tr("&View"));
        viewMenu->addAction(originalView);
        viewMenu->addAction(backgroundSubstractionView);
        viewMenu->addAction(handDetectionView);
        viewMenu->addAction(matchView);

        helpMenu = menuBar()->addMenu(tr("&Help"));
        helpMenu->addAction(aboutAct);
        helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{

}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


void MainWindow::readSettings()
{
    QSettings settings("NITK Surathkal", "Talk to the Hand");
    QPoint pos = settings.value("pos", QPoint(50, 50)).toPoint();
    QSize size = settings.value("size", QSize(1000, 700)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
   QSettings settings("NITK Surathkal", "Talk to the Hand");
   settings.setValue("pos", pos());
   settings.setValue("size", size());
}


void MainWindow::showBackgroundSubstractionView()
{

}

void MainWindow::showHandDetectionView()
{

}

void MainWindow::showOriginalView()
{

}

void MainWindow::showMatchView()
{

}
