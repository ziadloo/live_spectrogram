/****************************************************************************
** Meta object code from reading C++ file 'buffer_and_save.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../operations/buffer_and_save.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buffer_and_save.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_buffer_and_save_t {
    QByteArrayData data[7];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_buffer_and_save_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_buffer_and_save_t qt_meta_stringdata_buffer_and_save = {
    {
QT_MOC_LITERAL(0, 0, 15), // "buffer_and_save"
QT_MOC_LITERAL(1, 16, 11), // "set_vectors"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "vector_double"
QT_MOC_LITERAL(4, 43, 8), // "spectrum"
QT_MOC_LITERAL(5, 52, 10), // "similarity"
QT_MOC_LITERAL(6, 63, 6) // "noises"

    },
    "buffer_and_save\0set_vectors\0\0vector_double\0"
    "spectrum\0similarity\0noises"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_buffer_and_save[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,

       0        // eod
};

void buffer_and_save::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<buffer_and_save *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->set_vectors((*reinterpret_cast< vector_double(*)>(_a[1])),(*reinterpret_cast< vector_double(*)>(_a[2])),(*reinterpret_cast< vector_double(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject buffer_and_save::staticMetaObject = { {
    QMetaObject::SuperData::link<raw_operation::staticMetaObject>(),
    qt_meta_stringdata_buffer_and_save.data,
    qt_meta_data_buffer_and_save,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *buffer_and_save::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *buffer_and_save::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_buffer_and_save.stringdata0))
        return static_cast<void*>(this);
    return raw_operation::qt_metacast(_clname);
}

int buffer_and_save::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = raw_operation::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
