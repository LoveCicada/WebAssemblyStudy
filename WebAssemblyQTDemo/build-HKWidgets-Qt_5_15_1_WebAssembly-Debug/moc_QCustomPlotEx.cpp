/****************************************************************************
** Meta object code from reading C++ file 'QCustomPlotEx.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../HKWidgets/QCustomPlotEx.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCustomPlotEx.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QCustomPlotEx_t {
    QByteArrayData data[17];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCustomPlotEx_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCustomPlotEx_t qt_meta_stringdata_QCustomPlotEx = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QCustomPlotEx"
QT_MOC_LITERAL(1, 14, 9), // "SyncCross"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "QPoint&"
QT_MOC_LITERAL(4, 33, 5), // "point"
QT_MOC_LITERAL(5, 39, 14), // "SynEraserCross"
QT_MOC_LITERAL(6, 54, 11), // "SelectChart"
QT_MOC_LITERAL(7, 66, 14), // "QCustomPlotEx*"
QT_MOC_LITERAL(8, 81, 7), // "SynZoom"
QT_MOC_LITERAL(9, 89, 12), // "QWheelEvent*"
QT_MOC_LITERAL(10, 102, 5), // "event"
QT_MOC_LITERAL(11, 108, 8), // "SynTrans"
QT_MOC_LITERAL(12, 117, 12), // "QMouseEvent*"
QT_MOC_LITERAL(13, 130, 8), // "SynPress"
QT_MOC_LITERAL(14, 139, 10), // "SynRelease"
QT_MOC_LITERAL(15, 150, 12), // "onMouseWheel"
QT_MOC_LITERAL(16, 163, 12) // "playLineSlot"

    },
    "QCustomPlotEx\0SyncCross\0\0QPoint&\0point\0"
    "SynEraserCross\0SelectChart\0QCustomPlotEx*\0"
    "SynZoom\0QWheelEvent*\0event\0SynTrans\0"
    "QMouseEvent*\0SynPress\0SynRelease\0"
    "onMouseWheel\0playLineSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCustomPlotEx[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,
       6,    1,   63,    2, 0x06 /* Public */,
       8,    1,   66,    2, 0x06 /* Public */,
      11,    1,   69,    2, 0x06 /* Public */,
      13,    1,   72,    2, 0x06 /* Public */,
      14,    1,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    1,   78,    2, 0x0a /* Public */,
      16,    0,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   10,
    QMetaType::Void, 0x80000000 | 12,   10,
    QMetaType::Void, 0x80000000 | 12,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,

       0        // eod
};

void QCustomPlotEx::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCustomPlotEx *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SyncCross((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->SynEraserCross(); break;
        case 2: _t->SelectChart((*reinterpret_cast< QCustomPlotEx*(*)>(_a[1]))); break;
        case 3: _t->SynZoom((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 4: _t->SynTrans((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->SynPress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->SynRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 7: _t->onMouseWheel((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 8: _t->playLineSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlotEx* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCustomPlotEx::*)(QPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCustomPlotEx::SyncCross)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCustomPlotEx::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCustomPlotEx::SynEraserCross)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCustomPlotEx::*)(QCustomPlotEx * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCustomPlotEx::SelectChart)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QCustomPlotEx::*)(QWheelEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCustomPlotEx::SynZoom)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QCustomPlotEx::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCustomPlotEx::SynTrans)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QCustomPlotEx::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCustomPlotEx::SynPress)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QCustomPlotEx::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCustomPlotEx::SynRelease)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QCustomPlotEx::staticMetaObject = { {
    QMetaObject::SuperData::link<QCustomPlot::staticMetaObject>(),
    qt_meta_stringdata_QCustomPlotEx.data,
    qt_meta_data_QCustomPlotEx,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QCustomPlotEx::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCustomPlotEx::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCustomPlotEx.stringdata0))
        return static_cast<void*>(this);
    return QCustomPlot::qt_metacast(_clname);
}

int QCustomPlotEx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCustomPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QCustomPlotEx::SyncCross(QPoint & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCustomPlotEx::SynEraserCross()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QCustomPlotEx::SelectChart(QCustomPlotEx * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCustomPlotEx::SynZoom(QWheelEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QCustomPlotEx::SynTrans(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QCustomPlotEx::SynPress(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QCustomPlotEx::SynRelease(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
