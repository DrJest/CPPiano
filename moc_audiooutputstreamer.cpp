/****************************************************************************
** Meta object code from reading C++ file 'audiooutputstreamer.hpp'
**
** Created: Thu Nov 6 16:47:44 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "audiooutputstreamer.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audiooutputstreamer.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AudioOutputStreamer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AudioOutputStreamer[] = {
    "AudioOutputStreamer\0\0slot_writeMoreData()\0"
};

void AudioOutputStreamer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AudioOutputStreamer *_t = static_cast<AudioOutputStreamer *>(_o);
        switch (_id) {
        case 0: _t->slot_writeMoreData(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AudioOutputStreamer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AudioOutputStreamer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AudioOutputStreamer,
      qt_meta_data_AudioOutputStreamer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AudioOutputStreamer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AudioOutputStreamer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AudioOutputStreamer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AudioOutputStreamer))
        return static_cast<void*>(const_cast< AudioOutputStreamer*>(this));
    return QObject::qt_metacast(_clname);
}

int AudioOutputStreamer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
