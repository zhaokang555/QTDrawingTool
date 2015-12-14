/****************************************************************************
** Meta object code from reading C++ file 'paintwidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DrawingTool_ZK/paintwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paintwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PaintWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x0a,
      44,   12,   12,   12, 0x0a,
      51,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PaintWidget[] = {
    "PaintWidget\0\0s\0setCurrentShape(Shape::Code)\0"
    "undo()\0clearAll()\0"
};

void PaintWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PaintWidget *_t = static_cast<PaintWidget *>(_o);
        switch (_id) {
        case 0: _t->setCurrentShape((*reinterpret_cast< Shape::Code(*)>(_a[1]))); break;
        case 1: _t->undo(); break;
        case 2: _t->clearAll(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PaintWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PaintWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PaintWidget,
      qt_meta_data_PaintWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PaintWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PaintWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PaintWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PaintWidget))
        return static_cast<void*>(const_cast< PaintWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PaintWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
