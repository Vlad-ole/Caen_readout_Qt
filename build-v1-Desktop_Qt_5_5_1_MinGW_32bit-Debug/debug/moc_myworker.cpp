/****************************************************************************
** Meta object code from reading C++ file 'myworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../v1/myworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyWorker_t {
    QByteArrayData data[26];
    char stringdata0[359];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyWorker_t qt_meta_stringdata_MyWorker = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MyWorker"
QT_MOC_LITERAL(1, 9, 7), // "Message"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "finished"
QT_MOC_LITERAL(4, 27, 22), // "InitializationComplete"
QT_MOC_LITERAL(5, 50, 12), // "RedrawGraphs"
QT_MOC_LITERAL(6, 63, 15), // "QVector<double>"
QT_MOC_LITERAL(7, 79, 16), // "RedrawGraphsFull"
QT_MOC_LITERAL(8, 96, 25), // "QVector<QVector<double> >"
QT_MOC_LITERAL(9, 122, 13), // "TransferSpeed"
QT_MOC_LITERAL(10, 136, 11), // "TriggerRate"
QT_MOC_LITERAL(11, 148, 16), // "RedrawGraphsTest"
QT_MOC_LITERAL(12, 165, 4), // "Init"
QT_MOC_LITERAL(13, 170, 12), // "Readout_loop"
QT_MOC_LITERAL(14, 183, 7), // "Restart"
QT_MOC_LITERAL(15, 191, 11), // "QuitProgram"
QT_MOC_LITERAL(16, 203, 16), // "StopReadout_loop"
QT_MOC_LITERAL(17, 220, 17), // "ContinuousTrigger"
QT_MOC_LITERAL(18, 238, 15), // "ContinuousWrite"
QT_MOC_LITERAL(19, 254, 15), // "SetRecordLength"
QT_MOC_LITERAL(20, 270, 5), // "value"
QT_MOC_LITERAL(21, 276, 11), // "TestPattern"
QT_MOC_LITERAL(22, 288, 20), // "EnableContinuousPlot"
QT_MOC_LITERAL(23, 309, 21), // "DisableContinuousPlot"
QT_MOC_LITERAL(24, 331, 11), // "MaskChannel"
QT_MOC_LITERAL(25, 343, 15) // "SetTriggerValue"

    },
    "MyWorker\0Message\0\0finished\0"
    "InitializationComplete\0RedrawGraphs\0"
    "QVector<double>\0RedrawGraphsFull\0"
    "QVector<QVector<double> >\0TransferSpeed\0"
    "TriggerRate\0RedrawGraphsTest\0Init\0"
    "Readout_loop\0Restart\0QuitProgram\0"
    "StopReadout_loop\0ContinuousTrigger\0"
    "ContinuousWrite\0SetRecordLength\0value\0"
    "TestPattern\0EnableContinuousPlot\0"
    "DisableContinuousPlot\0MaskChannel\0"
    "SetTriggerValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  119,    2, 0x06 /* Public */,
       3,    0,  122,    2, 0x06 /* Public */,
       4,    0,  123,    2, 0x06 /* Public */,
       5,    2,  124,    2, 0x06 /* Public */,
       7,    2,  129,    2, 0x06 /* Public */,
       9,    1,  134,    2, 0x06 /* Public */,
      10,    1,  137,    2, 0x06 /* Public */,
      11,    0,  140,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  141,    2, 0x0a /* Public */,
      13,    0,  142,    2, 0x0a /* Public */,
      14,    0,  143,    2, 0x0a /* Public */,
      15,    0,  144,    2, 0x0a /* Public */,
      16,    0,  145,    2, 0x0a /* Public */,
      17,    0,  146,    2, 0x0a /* Public */,
      18,    0,  147,    2, 0x0a /* Public */,
      19,    1,  148,    2, 0x0a /* Public */,
      21,    0,  151,    2, 0x0a /* Public */,
      22,    0,  152,    2, 0x0a /* Public */,
      23,    0,  153,    2, 0x0a /* Public */,
      24,    2,  154,    2, 0x0a /* Public */,
      25,    2,  159,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    2,    2,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    2,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

       0        // eod
};

void MyWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyWorker *_t = static_cast<MyWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->finished(); break;
        case 2: _t->InitializationComplete(); break;
        case 3: _t->RedrawGraphs((*reinterpret_cast< QVector<double>(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2]))); break;
        case 4: _t->RedrawGraphsFull((*reinterpret_cast< QVector<double>(*)>(_a[1])),(*reinterpret_cast< QVector<QVector<double> >(*)>(_a[2]))); break;
        case 5: _t->TransferSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->TriggerRate((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->RedrawGraphsTest(); break;
        case 8: _t->Init(); break;
        case 9: _t->Readout_loop(); break;
        case 10: _t->Restart(); break;
        case 11: _t->QuitProgram(); break;
        case 12: _t->StopReadout_loop(); break;
        case 13: _t->ContinuousTrigger(); break;
        case 14: _t->ContinuousWrite(); break;
        case 15: _t->SetRecordLength((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->TestPattern(); break;
        case 17: _t->EnableContinuousPlot(); break;
        case 18: _t->DisableContinuousPlot(); break;
        case 19: _t->MaskChannel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 20: _t->SetTriggerValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyWorker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::Message)) {
                *result = 0;
            }
        }
        {
            typedef void (MyWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::finished)) {
                *result = 1;
            }
        }
        {
            typedef void (MyWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::InitializationComplete)) {
                *result = 2;
            }
        }
        {
            typedef void (MyWorker::*_t)(QVector<double> , QVector<double> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::RedrawGraphs)) {
                *result = 3;
            }
        }
        {
            typedef void (MyWorker::*_t)(QVector<double> , QVector<QVector<double> > );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::RedrawGraphsFull)) {
                *result = 4;
            }
        }
        {
            typedef void (MyWorker::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::TransferSpeed)) {
                *result = 5;
            }
        }
        {
            typedef void (MyWorker::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::TriggerRate)) {
                *result = 6;
            }
        }
        {
            typedef void (MyWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::RedrawGraphsTest)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject MyWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyWorker.data,
      qt_meta_data_MyWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyWorker.stringdata0))
        return static_cast<void*>(const_cast< MyWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int MyWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void MyWorker::Message(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyWorker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MyWorker::InitializationComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void MyWorker::RedrawGraphs(QVector<double> _t1, QVector<double> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyWorker::RedrawGraphsFull(QVector<double> _t1, QVector<QVector<double> > _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyWorker::TransferSpeed(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MyWorker::TriggerRate(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MyWorker::RedrawGraphsTest()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
