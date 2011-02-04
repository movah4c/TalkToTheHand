#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cstdio>
#include <cassert>
#include <QWidget>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QGridLayout>
#include "QOpenCVWidget.h"
#include "cameraWindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void showOriginalView();
    void showBackgroundSubstractionView();
    void showHandDetectionView();
    void showMatchView();
    void about();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();



    QPlainTextEdit *textEdit;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *originalView;
    QAction *backgroundSubstractionView;
    QAction *handDetectionView;
    QAction *matchView;

    CameraWindow *openCVCameraWindow;
    CvCapture* camera;
    CameraWindow *backgroundSubWindow;
    CameraWindow *handDetectWindow;
    CameraWindow *matchWindow;
    QGridLayout *mainLayout;

};

#endif // MAINWINDOW_H
