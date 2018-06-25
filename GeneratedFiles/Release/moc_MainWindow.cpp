/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Heat_t {
    QByteArrayData data[3];
    char stringdata0[9];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Heat_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Heat_t qt_meta_stringdata_Heat = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Heat"
QT_MOC_LITERAL(1, 5, 2), // "Do"
QT_MOC_LITERAL(2, 8, 0) // ""

    },
    "Heat\0Do\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Heat[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Heat::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Heat *_t = static_cast<Heat *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Do(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Heat::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Heat.data,
      qt_meta_data_Heat,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Heat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Heat::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Heat.stringdata0))
        return static_cast<void*>(const_cast< Heat*>(this));
    return QObject::qt_metacast(_clname);
}

int Heat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[42];
    char stringdata0[636];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "fullScreen"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "checked"
QT_MOC_LITERAL(4, 31, 11), // "OpenProject"
QT_MOC_LITERAL(5, 43, 10), // "NewProject"
QT_MOC_LITERAL(6, 54, 13), // "SaveAsProject"
QT_MOC_LITERAL(7, 68, 14), // "slotEscPressed"
QT_MOC_LITERAL(8, 83, 14), // "slotAnnoAdding"
QT_MOC_LITERAL(9, 98, 19), // "slotAnnoAddFinished"
QT_MOC_LITERAL(10, 118, 19), // "slotDataTimeChanged"
QT_MOC_LITERAL(11, 138, 8), // "dataTime"
QT_MOC_LITERAL(12, 147, 21), // "slotSliderHourChanged"
QT_MOC_LITERAL(13, 169, 6), // "nValue"
QT_MOC_LITERAL(14, 176, 16), // "slotSetCameraPos"
QT_MOC_LITERAL(15, 193, 11), // "slotRefresh"
QT_MOC_LITERAL(16, 205, 14), // "slotDetectTool"
QT_MOC_LITERAL(17, 220, 8), // "slotTest"
QT_MOC_LITERAL(18, 229, 14), // "loadCameraPath"
QT_MOC_LITERAL(19, 244, 21), // "slotDirectManipulator"
QT_MOC_LITERAL(20, 266, 14), // "loadTargetPath"
QT_MOC_LITERAL(21, 281, 14), // "startAnmiation"
QT_MOC_LITERAL(22, 296, 13), // "StopAnimation"
QT_MOC_LITERAL(23, 310, 15), // "OutputAnimation"
QT_MOC_LITERAL(24, 326, 16), // "slotSavePicAsTxt"
QT_MOC_LITERAL(25, 343, 13), // "MakeAnimation"
QT_MOC_LITERAL(26, 357, 17), // "AnimationSettings"
QT_MOC_LITERAL(27, 375, 18), // "addModisRadioLayer"
QT_MOC_LITERAL(28, 394, 24), // "addModisTemperatureLayer"
QT_MOC_LITERAL(29, 419, 13), // "addModelLayer"
QT_MOC_LITERAL(30, 433, 13), // "addAnnotation"
QT_MOC_LITERAL(31, 447, 13), // "addTargetData"
QT_MOC_LITERAL(32, 461, 10), // "addAirData"
QT_MOC_LITERAL(33, 472, 19), // "slotSetJetthreshold"
QT_MOC_LITERAL(34, 492, 10), // "Target2plt"
QT_MOC_LITERAL(35, 503, 7), // "LoadPlt"
QT_MOC_LITERAL(36, 511, 21), // "terrainProfileToggled"
QT_MOC_LITERAL(37, 533, 17), // "slotSetRenderMode"
QT_MOC_LITERAL(38, 551, 24), // "slotDataTranslateToRadio"
QT_MOC_LITERAL(39, 576, 18), // "slotFixedAngleMode"
QT_MOC_LITERAL(40, 595, 21), // "slotRefreshTargetData"
QT_MOC_LITERAL(41, 617, 18) // "slotRefreshAirData"

    },
    "MainWindow\0fullScreen\0\0checked\0"
    "OpenProject\0NewProject\0SaveAsProject\0"
    "slotEscPressed\0slotAnnoAdding\0"
    "slotAnnoAddFinished\0slotDataTimeChanged\0"
    "dataTime\0slotSliderHourChanged\0nValue\0"
    "slotSetCameraPos\0slotRefresh\0"
    "slotDetectTool\0slotTest\0loadCameraPath\0"
    "slotDirectManipulator\0loadTargetPath\0"
    "startAnmiation\0StopAnimation\0"
    "OutputAnimation\0slotSavePicAsTxt\0"
    "MakeAnimation\0AnimationSettings\0"
    "addModisRadioLayer\0addModisTemperatureLayer\0"
    "addModelLayer\0addAnnotation\0addTargetData\0"
    "addAirData\0slotSetJetthreshold\0"
    "Target2plt\0LoadPlt\0terrainProfileToggled\0"
    "slotSetRenderMode\0slotDataTranslateToRadio\0"
    "slotFixedAngleMode\0slotRefreshTargetData\0"
    "slotRefreshAirData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  199,    2, 0x09 /* Protected */,
       4,    0,  202,    2, 0x09 /* Protected */,
       5,    0,  203,    2, 0x09 /* Protected */,
       6,    0,  204,    2, 0x09 /* Protected */,
       7,    0,  205,    2, 0x09 /* Protected */,
       8,    0,  206,    2, 0x09 /* Protected */,
       9,    0,  207,    2, 0x09 /* Protected */,
      10,    1,  208,    2, 0x09 /* Protected */,
      12,    1,  211,    2, 0x09 /* Protected */,
      14,    0,  214,    2, 0x09 /* Protected */,
      15,    0,  215,    2, 0x09 /* Protected */,
      16,    0,  216,    2, 0x09 /* Protected */,
      17,    0,  217,    2, 0x08 /* Private */,
      18,    0,  218,    2, 0x08 /* Private */,
      19,    0,  219,    2, 0x08 /* Private */,
      20,    0,  220,    2, 0x08 /* Private */,
      21,    0,  221,    2, 0x08 /* Private */,
      22,    0,  222,    2, 0x08 /* Private */,
      23,    0,  223,    2, 0x08 /* Private */,
      24,    0,  224,    2, 0x08 /* Private */,
      25,    0,  225,    2, 0x08 /* Private */,
      26,    0,  226,    2, 0x08 /* Private */,
      27,    0,  227,    2, 0x08 /* Private */,
      28,    0,  228,    2, 0x08 /* Private */,
      29,    0,  229,    2, 0x08 /* Private */,
      30,    0,  230,    2, 0x08 /* Private */,
      31,    0,  231,    2, 0x08 /* Private */,
      32,    0,  232,    2, 0x08 /* Private */,
      33,    0,  233,    2, 0x08 /* Private */,
      34,    0,  234,    2, 0x08 /* Private */,
      35,    0,  235,    2, 0x08 /* Private */,
      36,    1,  236,    2, 0x08 /* Private */,
      37,    0,  239,    2, 0x08 /* Private */,
      38,    0,  240,    2, 0x08 /* Private */,
      39,    1,  241,    2, 0x08 /* Private */,
      40,    0,  244,    2, 0x08 /* Private */,
      41,    0,  245,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDateTime,   11,
    QMetaType::Void, QMetaType::Int,   13,
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
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->OpenProject(); break;
        case 2: _t->NewProject(); break;
        case 3: _t->SaveAsProject(); break;
        case 4: _t->slotEscPressed(); break;
        case 5: _t->slotAnnoAdding(); break;
        case 6: _t->slotAnnoAddFinished(); break;
        case 7: _t->slotDataTimeChanged((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 8: _t->slotSliderHourChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotSetCameraPos(); break;
        case 10: _t->slotRefresh(); break;
        case 11: _t->slotDetectTool(); break;
        case 12: _t->slotTest(); break;
        case 13: _t->loadCameraPath(); break;
        case 14: _t->slotDirectManipulator(); break;
        case 15: _t->loadTargetPath(); break;
        case 16: _t->startAnmiation(); break;
        case 17: _t->StopAnimation(); break;
        case 18: _t->OutputAnimation(); break;
        case 19: _t->slotSavePicAsTxt(); break;
        case 20: _t->MakeAnimation(); break;
        case 21: _t->AnimationSettings(); break;
        case 22: _t->addModisRadioLayer(); break;
        case 23: _t->addModisTemperatureLayer(); break;
        case 24: _t->addModelLayer(); break;
        case 25: _t->addAnnotation(); break;
        case 26: _t->addTargetData(); break;
        case 27: _t->addAirData(); break;
        case 28: _t->slotSetJetthreshold(); break;
        case 29: _t->Target2plt(); break;
        case 30: _t->LoadPlt(); break;
        case 31: _t->terrainProfileToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->slotSetRenderMode(); break;
        case 33: _t->slotDataTranslateToRadio(); break;
        case 34: _t->slotFixedAngleMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->slotRefreshTargetData(); break;
        case 36: _t->slotRefreshAirData(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &RibbonWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return RibbonWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RibbonWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 37;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
