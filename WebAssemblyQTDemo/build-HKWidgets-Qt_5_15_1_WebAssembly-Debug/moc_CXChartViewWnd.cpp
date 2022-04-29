/****************************************************************************
** Meta object code from reading C++ file 'CXChartViewWnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../HKWidgets/CXChartViewWnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CXChartViewWnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CXChartViewWnd_t {
    QByteArrayData data[16];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CXChartViewWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CXChartViewWnd_t qt_meta_stringdata_CXChartViewWnd = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CXChartViewWnd"
QT_MOC_LITERAL(1, 15, 13), // "controlHandle"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "std::string"
QT_MOC_LITERAL(4, 42, 11), // "strControll"
QT_MOC_LITERAL(5, 54, 17), // "updateChartHandle"
QT_MOC_LITERAL(6, 72, 18), // "openCrossBtnHandle"
QT_MOC_LITERAL(7, 91, 13), // "fullBtnHandle"
QT_MOC_LITERAL(8, 105, 15), // "rotateBtnHandle"
QT_MOC_LITERAL(9, 121, 14), // "transBtnHandle"
QT_MOC_LITERAL(10, 136, 13), // "moveBtnHandle"
QT_MOC_LITERAL(11, 150, 12), // "setBtnHandle"
QT_MOC_LITERAL(12, 163, 16), // "moveUpMenuHandle"
QT_MOC_LITERAL(13, 180, 18), // "moveDownMenuHandle"
QT_MOC_LITERAL(14, 199, 14), // "paramSetHandle"
QT_MOC_LITERAL(15, 214, 19) // "backToDefaultHandle"

    },
    "CXChartViewWnd\0controlHandle\0\0std::string\0"
    "strControll\0updateChartHandle\0"
    "openCrossBtnHandle\0fullBtnHandle\0"
    "rotateBtnHandle\0transBtnHandle\0"
    "moveBtnHandle\0setBtnHandle\0moveUpMenuHandle\0"
    "moveDownMenuHandle\0paramSetHandle\0"
    "backToDefaultHandle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CXChartViewWnd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,
      14,    0,   86,    2, 0x0a /* Public */,
      15,    0,   87,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
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

       0        // eod
};

void CXChartViewWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CXChartViewWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->controlHandle((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 1: _t->updateChartHandle(); break;
        case 2: _t->openCrossBtnHandle(); break;
        case 3: _t->fullBtnHandle(); break;
        case 4: _t->rotateBtnHandle(); break;
        case 5: _t->transBtnHandle(); break;
        case 6: _t->moveBtnHandle(); break;
        case 7: _t->setBtnHandle(); break;
        case 8: _t->moveUpMenuHandle(); break;
        case 9: _t->moveDownMenuHandle(); break;
        case 10: _t->paramSetHandle(); break;
        case 11: _t->backToDefaultHandle(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CXChartViewWnd::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CXChartViewWnd.data,
    qt_meta_data_CXChartViewWnd,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CXChartViewWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CXChartViewWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CXChartViewWnd.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CXChartViewWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
