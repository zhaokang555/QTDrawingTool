#include "paintwidget.h"
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include "line.h"
#include "rect.h"
#include "circle.h"
#include <QPen>
#include <QColor>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent), currentShapeCode(Shape::Line), shape(NULL), endDraw(false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 设置画布填充颜色为白色
    painter.fillRect(this->rect(), Qt::white);
    // 设置填充颜色为透明
    painter.setBrush(Qt::transparent);

    // 依次绘制shapeList里的图形
    // 可以这么写
    foreach(Shape * shape, shapeList) {
        shape->paint(painter);
    }
    // 也可以这么写
//    QList<Shape*>::const_iterator i = shapeList.begin();
//    while (i != shapeList.end()) {
//        (*i)->paint(painter);
//        ++i;
//    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    switch (currentShapeCode) {
    case Shape::Line: {
        shape = new Line(this);     break;
    }
    case Shape::Rect: {
        shape = new Rect(this);     break;
    }
    case Shape::Circle: {
        shape = new Circle(this);
    }
    }
    if(shape != NULL) {
        endDraw = false;
        shapeList<<shape;
        shape->setStart(event->pos());
        shape->setEnd(event->pos());
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(shape && !endDraw) {
        shape->setEnd(event->pos());
//        repaint();
        update(); // update方法效果更好,能减少颤动
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    endDraw = true;
}

void PaintWidget::undo()
{
    if (!shapeList.empty())
        shapeList.pop_back();

    update();
}

void PaintWidget::clearAll()
{
    shapeList.clear();
//    下边的三种方法都可以
//    repaint();
//    repaint(0, 0, size().width(), size().height());
    update();
}


