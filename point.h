#ifndef POINT_H
#define POINT_H

#include<QPoint>

class Point : public QPoint
{
public:
    Point(QPoint point, double pressure);
    Point(int X, int Y, double pressure);
    double getPressure();
    void setPressure(double pressure);

private:
    double pressure;
};

#endif // POINT_H
