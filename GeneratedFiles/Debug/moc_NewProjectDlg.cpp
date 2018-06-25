/****************************************************************************
** Meta object code from reading C++ file 'NewProjectDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../NewProjectDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewProjectDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NewProjectDlg_t {
    QByteArrayData data[14];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NewProjectDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NewProjectDlg_t qt_meta_stringdata_NewProjectDlg = {
    {
QT_MOC_LITERAL(0, 0, 13), // "NewProjectDlg"
QT_MOC_LITERAL(1, 14, 15), // "slotProjectPath"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "slotCameraPath"
QT_MOC_LITERAL(4, 46, 14), // "slotTargetPath"
QT_MOC_LITERAL(5, 61, 14), // "slotAirDataDir"
QT_MOC_LITERAL(6, 76, 14), // "slotEarthRadio"
QT_MOC_LITERAL(7, 91, 7), // "slottmp"
QT_MOC_LITERAL(8, 99, 7), // "slotTRI"
QT_MOC_LITERAL(9, 107, 7), // "slotPlt"
QT_MOC_LITERAL(10, 115, 10), // "slotAddJet"
QT_MOC_LITERAL(11, 126, 13), // "slotDeleteJet"
QT_MOC_LITERAL(12, 140, 11), // "slotLoadJet"
QT_MOC_LITERAL(13, 152, 16) // "slotPushButtonOK"

    },
    "NewProjectDlg\0slotProjectPath\0\0"
    "slotCameraPath\0slotTargetPath\0"
    "slotAirDataDir\0slotEarthRadio\0slottmp\0"
    "slotTRI\0slotPlt\0slotAddJet\0slotDeleteJet\0"
    "slotLoadJet\0slotPushButtonOK"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewProjectDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,

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
    QMetaType::Void,

       0        // eod
};

void NewProjectDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NewProjectDlg *_t = static_cast<NewProjectDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotProjectPath(); break;
        case 1: _t->slotCameraPath(); break;
        case 2: _t->slotTargetPath(); break;
        case 3: _t->slotAirDataDir(); break;
        case 4: _t->slotEarthRadio(); break;
        case 5: _t->slottmp(); break;
        case 6: _t->slotTRI(); break;
        case 7: _t->slotPlt(); break;
        case 8: _t->slotAddJet(); break;
        case 9: _t->slotDeleteJet(); break;
        case 10: _t->slotLoadJet(); break;
        case 11: _t->slotPushButtonOK(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NewProjectDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewProjectDlg.data,
      qt_meta_data_NewProjectDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NewProjectDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewProjectDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NewProjectDlg.stringdata0))
        return static_cast<void*>(const_cast< NewProjectDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewProjectDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
