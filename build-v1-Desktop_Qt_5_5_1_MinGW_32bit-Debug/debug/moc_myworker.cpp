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
    QByteArrayData data[19];
    char stringdata0[233];
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
QT_MOC_LITERAL(7, 79, 13), // "TransferSpeed"
QT_MOC_LITERAL(8, 93, 11), // "TriggerRate"
QT_MOC_LITERAL(9, 105, 16), // "RedrawGraphsTest"
QT_MOC_LITERAL(10, 122, 4), // "Init"
QT_MOC_LITERAL(11, 127, 12), // "Readout_loop"
QT_MOC_LITERAL(12, 140, 7), // "Restart"
QT_MOC_LITERAL(13, 148, 11), // "QuitProgram"
QT_MOC_LITERAL(14, 160, 16), // "StopReadout_loop"
QT_MOC_LITERAL(15, 177, 17), // "ContinuousTrigger"
QT_MOC_LITERAL(16, 195, 15), // "ContinuousWrite"
QT_MOC_LITERAL(17, 211, 15), // "SetRecordLength"
QT_MOC_LITERAL(18, 227, 5) // "value"

    },
    "MyWorker\0Message\0\0finished\0"
    "InitializationComplete\0RedrawGraphs\0"
    "QVector<double>\0TransferSpeed\0TriggerRate\0"
    "RedrawGraphsTest\0Init\0Readout_loop\0"
    "Restart\0QuitProgram\0StopReadout_loop\0"
    "ContinuousTrigger\0ContinuousWrite\0"
    "SetRecordLength\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       3,    0,   92,    2, 0x06 /* Public */,
       4,    0,   93,    2, 0x06 /* Public */,
       5,    2,   94,    2, 0x06 /* Public */,
       7,    1,   99,    2, 0x06 /* Public */,
       8,    1,  102,    2, 0x06 /* Public */,
       9,    0,  105,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  106,    2, 0x0a /* Public */,
      11,    0,  107,    2, 0x0a /* Public */,
      12,    0,  108,    2, 0x0a /* Public */,
      13,    0,  109,    2, 0x0a /* Public */,
      14,    0,  110,    2, 0x0a /* Public */,
      15,    0,  111,    2, 0x0a /* Public */,
      16,    0,  112,    2, 0x0a /* Public */,
      17,    1,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    2,    2,
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
    QMetaType::Void, QMetaType::Double,   18,

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
        case 4: _t->TransferSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->TriggerRate((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->RedrawGraphsTest(); break;
        case 7: _t->Init(); break;
        case 8: _t->Readout_loop(); break;
        case 9: _t->Restart(); break;
        case 10: _t->QuitProgram(); break;
        case 11: _t->StopReadout_loop(); break;
        case 12: _t->ContinuousTrigger(); break;
        case 13: _t->ContinuousWrite(); break;
        case 14: _t->SetRecordLength((*reinterpret_cast< double(*)>(_a[1]))); break;
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
            typedef void (MyWorker::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::TransferSpeed)) {
                *result = 4;
            }
        }
        {
            typedef void (MyWorker::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::TriggerRate)) {
                *result = 5;
            }
        }
        {
            typedef void (MyWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyWorker::RedrawGraphsTest)) {
                *result = 6;
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
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
void MyWorker::TransferSpeed(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyWorker::TriggerRate(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MyWorker::RedrawGraphsTest()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
