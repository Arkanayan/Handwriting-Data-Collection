#include "point.h"

Point::Point(QPoint point, double pressure): QPoint(point), pressure(pressure)
{

}

Point::Point(int X, int Y, double pressure) : QPoint(X, Y), pressure(pressure)
{

}


void Point::setPressure(const double pressure) {
    this->pressure = pressure;
}

double Point::getPressure() const {
    return this->pressure;
}
