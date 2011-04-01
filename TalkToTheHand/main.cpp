/**
 * Application Name: TalkToTheHand
 * Version         : 1.0
 * Organization    : IT Department, NITK Surathkal
 * Description     : This application helps to recognize one hand gestures based
 *                   on American Sign Language(ASL) and converts them into words
 *                   which are spoken later on by the text to speech module. The
 *                   the characters recognized are also displayed in the text bar
 *                   at the bottom of the screen.
 */

#include <QApplication>
#include <QSplashScreen>
#include "mainwindow.h"

int main(int argc, char *argv[])
{


    Q_INIT_RESOURCE(icons); /** Initializing the icon images for the application. */

    /** Application object for creating the application */
    QApplication app(argc, argv);
    /** Providing application settings */
    app.setOrganizationName("NITK Surathkal");
    app.setApplicationName("Talk To The Hand");
    app.setApplicationVersion("Version 1.0");
    app.setWindowIcon(QIcon(":/images/logo.jpg"));

    /** Initializing splash screen for the application */
    QSplashScreen *splash = new QSplashScreen;
    QImage *splashImage = new QImage(":/images/SplashScreen.jpg");
    *splashImage = splashImage->scaledToHeight(300);
    splash->setPixmap(QPixmap::fromImage(*splashImage));
    splash->show();
    Qt::Alignment topRight = Qt::AlignLeft | Qt::AlignBottom;
    splash->showMessage(QObject::tr("Initializing..."),topRight, Qt::black);
    sleep(3);

    /** Creating mainwindow of the application and then showing it*/
    MainWindow mainWin;
    mainWin.show();
    //mainWin.showFullScreen();

    /** Remove splash screen as soon as the window loads */
    splash->finish(&mainWin);
    delete splash;

    return app.exec();
}
