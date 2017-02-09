#ifndef STRIDE_H
#define STRIDE_H

#include <QObject>
#include <QList>
#include "point.h"

class Stride
{
public:
    Stride();
    QList<Point> points;
    void addPoint(const Point point);

};

#endif // STRIDE_H
