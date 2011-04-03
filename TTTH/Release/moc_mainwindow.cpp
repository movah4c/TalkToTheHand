/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Apr 3 16:58:17 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x05,
      51,   37,   11,   11, 0x05,
      92,   86,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     118,  116,   11,   11, 0x0a,
     150,   11,   11,   11, 0x08,
     158,   11,   11,   11, 0x08,
     170,   11,   11,   11, 0x08,
     182,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,
     219,   11,   11,   11, 0x08,
     226,   11,   11,   11, 0x08,
     235,   11,   11,   11, 0x08,
     248,   11,   11,   11, 0x08,
     267,   11,   11,   11, 0x08,
     284,   11,   11,   11, 0x08,
     294,   11,   11,   11, 0x08,
     308,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0type\0ViewTypeChange(int)\0"
    "type,filename\0operationalModeChange(int,QString)\0"
    "state\0changeRunningState(int)\0c\0"
    "displayRecognizedAlphabet(char)\0about()\0"
    "openImage()\0openVideo()\0startRecognition()\0"
    "stopRecognition()\0mute()\0volume()\0"
    "normalView()\0backroundSubView()\0"
    "handDetectView()\0options()\0trainerTool()\0"
    "applySettings()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ViewTypeChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: operationalModeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: changeRunningState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: displayRecognizedAlphabet((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 4: about(); break;
        case 5: openImage(); break;
        case 6: openVideo(); break;
        case 7: startRecognition(); break;
        case 8: stopRecognition(); break;
        case 9: mute(); break;
        case 10: volume(); break;
        case 11: normalView(); break;
        case 12: backroundSubView(); break;
        case 13: handDetectView(); break;
        case 14: options(); break;
        case 15: trainerTool(); break;
        case 16: applySettings(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::ViewTypeChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::operationalModeChange(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::changeRunningState(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
