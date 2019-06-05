#ifndef POINT_H
#define POINT_H
#include <QGraphicsItem>
#include <QPainter>

class Point : public QGraphicsItem
{
public:
    Point(int x, int y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    int xpos = 0, ypos = 0;
};

#endif // POINT_H
