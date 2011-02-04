#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    Q_INIT_RESOURCE(iconImages);
    QApplication app(argc, argv);
    app.setOrganizationName("NITK Surathkal");
    app.setApplicationName("Talk To The Hand");
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
    return 0;
}
