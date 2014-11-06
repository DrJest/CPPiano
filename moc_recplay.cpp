/****************************************************************************
** Meta object code from reading C++ file 'recplay.hpp'
**
** Created: Thu Nov 6 17:01:11 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "recplay.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recplay.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RecPlay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      20,    8,    8,    8, 0x0a,
      30,    8,    8,    8, 0x0a,
      37,    8,    8,    8, 0x0a,
      45,    8,    8,    8, 0x0a,
      52,    8,    8,    8, 0x0a,
      67,    8,    8,    8, 0x0a,
      75,    8,    8,    8, 0x0a,
      82,    8,    8,    8, 0x0a,
      89,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RecPlay[] = {
    "RecPlay\0\0startRec()\0stopRec()\0Play()\0"
    "Pause()\0Stop()\0PlayNextNote()\0Clear()\0"
    "Open()\0Save()\0SaveAs()\0"
};

void RecPlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RecPlay *_t = static_cast<RecPlay *>(_o);
        switch (_id) {
        case 0: _t->startRec(); break;
        case 1: _t->stopRec(); break;
        case 2: _t->Play(); break;
        case 3: _t->Pause(); break;
        case 4: _t->Stop(); break;
        case 5: _t->PlayNextNote(); break;
        case 6: _t->Clear(); break;
        case 7: _t->Open(); break;
        case 8: _t->Save(); break;
        case 9: _t->SaveAs(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData RecPlay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RecPlay::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RecPlay,
      qt_meta_data_RecPlay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RecPlay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RecPlay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RecPlay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RecPlay))
        return static_cast<void*>(const_cast< RecPlay*>(this));
    return QObject::qt_metacast(_clname);
}

int RecPlay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
