/****************************************************************************
** Meta object code from reading C++ file 'TransformWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "interface/inc/TransformWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TransformWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TransformWidget_t {
    QByteArrayData data[17];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TransformWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TransformWidget_t qt_meta_stringdata_TransformWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TransformWidget"
QT_MOC_LITERAL(1, 16, 16), // "loadModelClicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 16), // "loadSceneClicked"
QT_MOC_LITERAL(4, 51, 18), // "removeModelClicked"
QT_MOC_LITERAL(5, 70, 16), // "moveModelClicked"
QT_MOC_LITERAL(6, 87, 17), // "scaleModelClicked"
QT_MOC_LITERAL(7, 105, 18), // "rotateModelClicked"
QT_MOC_LITERAL(8, 124, 16), // "addCameraClicked"
QT_MOC_LITERAL(9, 141, 19), // "removeCameraClicked"
QT_MOC_LITERAL(10, 161, 17), // "moveCameraClicked"
QT_MOC_LITERAL(11, 179, 18), // "scaleCameraClicked"
QT_MOC_LITERAL(12, 198, 19), // "rotateCameraClicked"
QT_MOC_LITERAL(13, 218, 13), // "cameraChanged"
QT_MOC_LITERAL(14, 232, 5), // "index"
QT_MOC_LITERAL(15, 238, 12), // "modelChanged"
QT_MOC_LITERAL(16, 251, 12) // "sceneChanged"

    },
    "TransformWidget\0loadModelClicked\0\0"
    "loadSceneClicked\0removeModelClicked\0"
    "moveModelClicked\0scaleModelClicked\0"
    "rotateModelClicked\0addCameraClicked\0"
    "removeCameraClicked\0moveCameraClicked\0"
    "scaleCameraClicked\0rotateCameraClicked\0"
    "cameraChanged\0index\0modelChanged\0"
    "sceneChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransformWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    1,   95,    2, 0x08 /* Private */,
      15,    1,   98,    2, 0x08 /* Private */,
      16,    1,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void TransformWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TransformWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadModelClicked(); break;
        case 1: _t->loadSceneClicked(); break;
        case 2: _t->removeModelClicked(); break;
        case 3: _t->moveModelClicked(); break;
        case 4: _t->scaleModelClicked(); break;
        case 5: _t->rotateModelClicked(); break;
        case 6: _t->addCameraClicked(); break;
        case 7: _t->removeCameraClicked(); break;
        case 8: _t->moveCameraClicked(); break;
        case 9: _t->scaleCameraClicked(); break;
        case 10: _t->rotateCameraClicked(); break;
        case 11: _t->cameraChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->modelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->sceneChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TransformWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_TransformWidget.data,
    qt_meta_data_TransformWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TransformWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransformWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TransformWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TransformWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
