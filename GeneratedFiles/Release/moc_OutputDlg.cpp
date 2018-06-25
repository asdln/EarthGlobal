/****************************************************************************
** Meta object code from reading C++ file 'OutputDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../OutputDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OutputDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OutputDlg_t {
    QByteArrayData data[10];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OutputDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OutputDlg_t qt_meta_stringdata_OutputDlg = {
    {
QT_MOC_LITERAL(0, 0, 9), // "OutputDlg"
QT_MOC_LITERAL(1, 10, 11), // "slotSetPath"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "slotShowLastPic"
QT_MOC_LITERAL(4, 39, 15), // "slotOutputLevel"
QT_MOC_LITERAL(5, 55, 15), // "slotLeftAliment"
QT_MOC_LITERAL(6, 71, 16), // "slotRightAliment"
QT_MOC_LITERAL(7, 88, 15), // "slotOutputFloat"
QT_MOC_LITERAL(8, 104, 17), // "slotSelectAndOpen"
QT_MOC_LITERAL(9, 122, 17) // "slotSetStartFrame"

    },
    "OutputDlg\0slotSetPath\0\0slotShowLastPic\0"
    "slotOutputLevel\0slotLeftAliment\0"
    "slotRightAliment\0slotOutputFloat\0"
    "slotSelectAndOpen\0slotSetStartFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OutputDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    1,   56,    2, 0x0a /* Public */,
       5,    0,   59,    2, 0x0a /* Public */,
       6,    0,   60,    2, 0x0a /* Public */,
       7,    1,   61,    2, 0x0a /* Public */,
       8,    0,   64,    2, 0x0a /* Public */,
       9,    1,   65,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void OutputDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OutputDlg *_t = static_cast<OutputDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotSetPath(); break;
        case 1: _t->slotShowLastPic(); break;
        case 2: _t->slotOutputLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotLeftAliment(); break;
        case 4: _t->slotRightAliment(); break;
        case 5: _t->slotOutputFloat((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->slotSelectAndOpen(); break;
        case 7: _t->slotSetStartFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject OutputDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_OutputDlg.data,
      qt_meta_data_OutputDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OutputDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OutputDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OutputDlg.stringdata0))
        return static_cast<void*>(const_cast< OutputDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int OutputDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
