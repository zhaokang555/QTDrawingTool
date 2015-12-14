#include "rect.h"
#include <QPainter>

Rect::Rect(QObject *parent) : Shape(parent)
{
    shapeName = "Rect";
}

void Rect::paint(QPainter &painter) const
{
    painter.drawRect(start.x(), start.y(),
                     end.x() - start.x(), end.y() - start.y());
}
