/****************************************************************************
** Meta object code from reading C++ file 'control_panel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "control_panel/control_panel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'control_panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControlPanel_t {
    QByteArrayData data[9];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlPanel_t qt_meta_stringdata_ControlPanel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ControlPanel"
QT_MOC_LITERAL(1, 13, 4), // "call"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 2), // "fl"
QT_MOC_LITERAL(4, 22, 8), // "stayFree"
QT_MOC_LITERAL(5, 31, 7), // "atFloor"
QT_MOC_LITERAL(6, 39, 12), // "reachedFloor"
QT_MOC_LITERAL(7, 52, 12), // "setNewTarget"
QT_MOC_LITERAL(8, 65, 8) // "makeFree"

    },
    "ControlPanel\0call\0\0fl\0stayFree\0atFloor\0"
    "reachedFloor\0setNewTarget\0makeFree"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    0,   47,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   51,    2, 0x0a /* Public */,
       7,    1,   54,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void ControlPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControlPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->call((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->stayFree(); break;
        case 2: _t->atFloor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->reachedFloor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setNewTarget((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->makeFree(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ControlPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::call)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::stayFree)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ControlPanel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlPanel::atFloor)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ControlPanel::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ControlPanel.data,
    qt_meta_data_ControlPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ControlPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControlPanel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ControlPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ControlPanel::call(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControlPanel::stayFree()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ControlPanel::atFloor(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
