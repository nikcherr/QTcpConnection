#ifndef POINT_H
#define POINT_H
#include <QGraphicsItem>
#include <QPainter>

class Point : public QGraphicsItem
{
public:
    Point(int x, int y);
    Point();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPosition(int x, int y);

private:
    int xpos = 0, ypos = 0;
};

#endif // POINT_H
