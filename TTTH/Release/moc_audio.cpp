/****************************************************************************
** Meta object code from reading C++ file 'audio.h'
**
** Created: Sun Apr 3 16:58:22 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/audio.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayAudio[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   11,   10,   10, 0x08,
      29,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PlayAudio[] = {
    "PlayAudio\0\0time\0tick(qint64)\0"
    "aboutToFinish()\0"
};

const QMetaObject PlayAudio::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PlayAudio,
      qt_meta_data_PlayAudio, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayAudio::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayAudio::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayAudio::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayAudio))
        return static_cast<void*>(const_cast< PlayAudio*>(this));
    return QObject::qt_metacast(_clname);
}

int PlayAudio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tick((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: aboutToFinish(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
