

QT += phonon

LIBS += -lcv -lhighgui -lcvaux

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    audio.cpp \
    openCVWidget.cpp \
    cameraWidget.cpp



HEADERS += \
    mainwindow.h \
    audio.h \
    openCVWidget.h \
    cameraWidget.h \
    heap.h

RESOURCES += \
    icons.qrc
