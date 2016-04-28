#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QList>
#include "shape.h"
class QPaintEvent;
class QMouseEvent;

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = 0);

    QList<Shape*> shapeList;

public slots:
    void setCurrentShape(Shape::Code s) {
        if(s != currentShapeCode)
            currentShapeCode = s;  
    }

    void undo();
    void clearAll();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Shape::Code currentShapeCode;
    Shape *shape;
    bool endDraw;

};

#endif // PAINTWIDGET_H
