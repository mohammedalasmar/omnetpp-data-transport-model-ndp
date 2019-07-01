/****************************************************************************
** Meta object code from reading C++ file 'histograminspector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "histograminspector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'histograminspector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_omnetpp__qtenv__HistogramInspector_t {
    QByteArrayData data[10];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_omnetpp__qtenv__HistogramInspector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_omnetpp__qtenv__HistogramInspector_t qt_meta_stringdata_omnetpp__qtenv__HistogramInspector = {
    {
QT_MOC_LITERAL(0, 0, 34), // "omnetpp::qtenv::HistogramInsp..."
QT_MOC_LITERAL(1, 35, 14), // "onShowCellInfo"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 4), // "cell"
QT_MOC_LITERAL(4, 56, 28), // "onCustomContextMenuRequested"
QT_MOC_LITERAL(5, 85, 3), // "pos"
QT_MOC_LITERAL(6, 89, 12), // "onShowCounts"
QT_MOC_LITERAL(7, 102, 9), // "onShowPDF"
QT_MOC_LITERAL(8, 112, 18), // "onOptionsTriggered"
QT_MOC_LITERAL(9, 131, 20) // "onApplyButtonClicked"

    },
    "omnetpp::qtenv::HistogramInspector\0"
    "onShowCellInfo\0\0cell\0onCustomContextMenuRequested\0"
    "pos\0onShowCounts\0onShowPDF\0"
    "onOptionsTriggered\0onApplyButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_omnetpp__qtenv__HistogramInspector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    1,   47,    2, 0x08 /* Private */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    0,   51,    2, 0x08 /* Private */,
       8,    0,   52,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QPoint,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void omnetpp::qtenv::HistogramInspector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HistogramInspector *_t = static_cast<HistogramInspector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onShowCellInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onCustomContextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->onShowCounts(); break;
        case 3: _t->onShowPDF(); break;
        case 4: _t->onOptionsTriggered(); break;
        case 5: _t->onApplyButtonClicked(); break;
        default: ;
        }
    }
}

const QMetaObject omnetpp::qtenv::HistogramInspector::staticMetaObject = {
    { &Inspector::staticMetaObject, qt_meta_stringdata_omnetpp__qtenv__HistogramInspector.data,
      qt_meta_data_omnetpp__qtenv__HistogramInspector,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *omnetpp::qtenv::HistogramInspector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *omnetpp::qtenv::HistogramInspector::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_omnetpp__qtenv__HistogramInspector.stringdata0))
        return static_cast<void*>(const_cast< HistogramInspector*>(this));
    return Inspector::qt_metacast(_clname);
}

int omnetpp::qtenv::HistogramInspector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Inspector::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
