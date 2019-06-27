/****************************************************************************
** Meta object code from reading C++ file 'SCStatusTcp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SeerTCPTest-0.2.0/SCStatusTcp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SCStatusTcp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SCStatusTcp_t {
    QByteArrayData data[5];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SCStatusTcp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SCStatusTcp_t qt_meta_stringdata_SCStatusTcp = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SCStatusTcp"
QT_MOC_LITERAL(1, 12, 12), // "sigPrintInfo"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "sigChangedText"
QT_MOC_LITERAL(4, 41, 19) // "receiveTcpReadyRead"

    },
    "SCStatusTcp\0sigPrintInfo\0\0sigChangedText\0"
    "receiveTcpReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SCStatusTcp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    6,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::QByteArray, QMetaType::QByteArray, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void SCStatusTcp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SCStatusTcp *_t = static_cast<SCStatusTcp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigPrintInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sigChangedText((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3])),(*reinterpret_cast< QByteArray(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 2: _t->receiveTcpReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (SCStatusTcp::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCStatusTcp::sigPrintInfo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SCStatusTcp::*_t)(bool , int , QByteArray , QByteArray , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCStatusTcp::sigChangedText)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SCStatusTcp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SCStatusTcp.data,
      qt_meta_data_SCStatusTcp,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SCStatusTcp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SCStatusTcp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SCStatusTcp.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SCStatusTcp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SCStatusTcp::sigPrintInfo(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SCStatusTcp::sigChangedText(bool _t1, int _t2, QByteArray _t3, QByteArray _t4, int _t5, int _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
