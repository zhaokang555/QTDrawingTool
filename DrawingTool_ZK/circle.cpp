#include "Circle.h"
#include <cmath>
#include <QPainter>

Circle::Circle(QObject *parent) : Shape(parent)
{
    shapeName = "Circle";
}

void Circle::paint(QPainter & painter) const
{

    int len = pow(start.x() - end.x(), 2);
    int wid = pow(start.y() - end.y(), 2);
    // 利用勾股定理求出半径
    int r = (int)(sqrt(len + wid));
    painter.drawEllipse(start, r, r);
}
