/****************************************************************************
** Meta object code from reading C++ file 'CChartView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../HKWidgets/CChartView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CChartView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CChartView_t {
    QByteArrayData data[19];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CChartView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CChartView_t qt_meta_stringdata_CChartView = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CChartView"
QT_MOC_LITERAL(1, 11, 21), // "UpdateCurveDataSignal"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 8), // "QCPRange"
QT_MOC_LITERAL(4, 43, 5), // "range"
QT_MOC_LITERAL(5, 49, 11), // "SelectChart"
QT_MOC_LITERAL(6, 61, 14), // "QCustomPlotEx*"
QT_MOC_LITERAL(7, 76, 13), // "pCustomPlotEx"
QT_MOC_LITERAL(8, 90, 13), // "SyncCrossLine"
QT_MOC_LITERAL(9, 104, 5), // "point"
QT_MOC_LITERAL(10, 110, 19), // "SyncEraserCrossLine"
QT_MOC_LITERAL(11, 130, 11), // "SynZoomSlot"
QT_MOC_LITERAL(12, 142, 12), // "QWheelEvent*"
QT_MOC_LITERAL(13, 155, 5), // "event"
QT_MOC_LITERAL(14, 161, 12), // "SynTransSlot"
QT_MOC_LITERAL(15, 174, 12), // "QMouseEvent*"
QT_MOC_LITERAL(16, 187, 12), // "SynPressSlot"
QT_MOC_LITERAL(17, 200, 14), // "SynRelaeseSlot"
QT_MOC_LITERAL(18, 215, 19) // "UpdateCurveDataSlot"

    },
    "CChartView\0UpdateCurveDataSignal\0\0"
    "QCPRange\0range\0SelectChart\0QCustomPlotEx*\0"
    "pCustomPlotEx\0SyncCrossLine\0point\0"
    "SyncEraserCrossLine\0SynZoomSlot\0"
    "QWheelEvent*\0event\0SynTransSlot\0"
    "QMouseEvent*\0SynPressSlot\0SynRelaeseSlot\0"
    "UpdateCurveDataSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CChartView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   62,    2, 0x0a /* Public */,
       8,    1,   65,    2, 0x0a /* Public */,
      10,    0,   68,    2, 0x0a /* Public */,
      11,    1,   69,    2, 0x0a /* Public */,
      14,    1,   72,    2, 0x0a /* Public */,
      16,    1,   75,    2, 0x0a /* Public */,
      17,    1,   78,    2, 0x0a /* Public */,
      18,    1,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   13,
    QMetaType::Void, 0x80000000 | 15,   13,
    QMetaType::Void, 0x80000000 | 15,   13,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void CChartView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CChartView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateCurveDataSignal((*reinterpret_cast< const QCPRange(*)>(_a[1]))); break;
        case 1: _t->SelectChart((*reinterpret_cast< QCustomPlotEx*(*)>(_a[1]))); break;
        case 2: _t->SyncCrossLine((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 3: _t->SyncEraserCrossLine(); break;
        case 4: _t->SynZoomSlot((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 5: _t->SynTransSlot((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->SynPressSlot((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 7: _t->SynRelaeseSlot((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->UpdateCurveDataSlot((*reinterpret_cast< const QCPRange(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
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
            using _t = void (CChartView::*)(const QCPRange & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CChartView::UpdateCurveDataSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CChartView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CChartView.data,
    qt_meta_data_CChartView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CChartView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CChartView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CChartView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CChartView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void CChartView::UpdateCurveDataSignal(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
