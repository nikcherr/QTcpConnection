#include "line.h"

Line::Line()
{
    angleline = new QLineF();
    angleline->setP1(QPointF(0, 0));
    angleline->setP2(QPointF(0, 120));
}

void Line::setAzimuth(const float azimuth)
{
    this->angleline->setAngle(azimuth);
}

QRectF Line::boundingRect() const
{
    return QRectF(-250,-250,500,500);
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::blue);
    painter->drawLine(*angleline);
}
