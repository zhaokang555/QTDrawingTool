#ifndef RECT_H
#define RECT_H

#include "shape.h"

class Rect : public Shape
{

public:
    Rect(QObject *parent = 0);

    void paint(QPainter &painter) const;
};

#endif // RECT_H
