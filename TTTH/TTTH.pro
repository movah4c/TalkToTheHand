
QT += phonon

LIBS += -lcv -lhighgui -lcvaux

HEADERS += \
    include/settings.h \
    include/openCVWidget.h \
    include/matching.h \
    include/mainwindow.h \
    include/heap.h \
    include/cameraWidget.h \
    include/backgroundSubtraction.h \
    include/audio.h

SOURCES += \
    source/settings.cpp \
    source/openCVWidget.cpp \
    source/matching.cpp \
    source/mainwindow.cpp \
    source/main.cpp \
    source/cameraWidget.cpp \
    source/backgroundSubtraction.cpp \
    source/audio.cpp

RESOURCES += \
    icons.qrc
