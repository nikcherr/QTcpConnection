#include "point.h"

Point::Point(int x, int y)
    : xpos(x), ypos(y)

{

}

QRectF Point::boundingRect() const
{
    return QRectF(-25,-40,50,80);
}

void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    painter->setBrush(Qt::green);
    painter->drawEllipse(QPoint(xpos, ypos), 5, 5);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
