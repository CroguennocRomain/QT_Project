/****************************************************************************
** Meta object code from reading C++ file 'SpaceInvaders.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src2/SpaceInvaders.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SpaceInvaders.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_SpaceInvaders_t {
    uint offsetsAndSizes[14];
    char stringdata0[14];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[17];
    char stringdata5[11];
    char stringdata6[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_SpaceInvaders_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_SpaceInvaders_t qt_meta_stringdata_SpaceInvaders = {
    {
        QT_MOC_LITERAL(0, 13),  // "SpaceInvaders"
        QT_MOC_LITERAL(14, 13),  // "onCreateEnemy"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 15),  // "onIncreaseScore"
        QT_MOC_LITERAL(45, 16),  // "onDecreaseHealth"
        QT_MOC_LITERAL(62, 10),  // "onGameOver"
        QT_MOC_LITERAL(73, 6)   // "update"
    },
    "SpaceInvaders",
    "onCreateEnemy",
    "",
    "onIncreaseScore",
    "onDecreaseHealth",
    "onGameOver",
    "update"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_SpaceInvaders[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x0a,    1 /* Public */,
       3,    0,   45,    2, 0x0a,    2 /* Public */,
       4,    0,   46,    2, 0x0a,    3 /* Public */,
       5,    0,   47,    2, 0x0a,    4 /* Public */,
       6,    0,   48,    2, 0x0a,    5 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SpaceInvaders::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_SpaceInvaders.offsetsAndSizes,
    qt_meta_data_SpaceInvaders,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_SpaceInvaders_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SpaceInvaders, std::true_type>,
        // method 'onCreateEnemy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onIncreaseScore'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDecreaseHealth'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onGameOver'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'update'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SpaceInvaders::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SpaceInvaders *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onCreateEnemy(); break;
        case 1: _t->onIncreaseScore(); break;
        case 2: _t->onDecreaseHealth(); break;
        case 3: _t->onGameOver(); break;
        case 4: _t->update(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *SpaceInvaders::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpaceInvaders::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpaceInvaders.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int SpaceInvaders::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE