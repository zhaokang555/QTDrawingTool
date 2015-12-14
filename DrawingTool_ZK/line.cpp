#include "line.h"
#include <QPainter>

Line::Line(QObject *parent) : Shape(parent)
{
    shapeName= "Line";
}

void Line::paint(QPainter &painter) const
{
    painter.drawLine(start, end);
}
