/****************************************************************************
** Meta object code from reading C++ file 'options.hpp'
**
** Created: Fri Dec 5 11:37:06 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "options.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'options.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_options[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      30,    8,    8,    8, 0x0a,
      60,    8,    8,    8, 0x0a,
      74,    8,    8,    8, 0x0a,
      86,    8,    8,    8, 0x0a,
     109,    8,    8,    8, 0x0a,
     133,    8,    8,    8, 0x0a,
     151,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_options[] = {
    "options\0\0spawnOptionsWindow()\0"
    "toggleLayoutCustomField(bool)\0"
    "saveOptions()\0cusBrowse()\0"
    "setDefaultLayout(bool)\0setCompleteLayout(bool)\0"
    "setMinOctave(int)\0setMaxOctave(int)\0"
};

void options::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        options *_t = static_cast<options *>(_o);
        switch (_id) {
        case 0: _t->spawnOptionsWindow(); break;
        case 1: _t->toggleLayoutCustomField((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->saveOptions(); break;
        case 3: _t->cusBrowse(); break;
        case 4: _t->setDefaultLayout((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setCompleteLayout((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setMinOctave((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setMaxOctave((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData options::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject options::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_options,
      qt_meta_data_options, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &options::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *options::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *options::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_options))
        return static_cast<void*>(const_cast< options*>(this));
    return QObject::qt_metacast(_clname);
}

int options::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
