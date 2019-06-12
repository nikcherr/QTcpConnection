#ifndef LINE_H
#define LINE_H
#include <QGraphicsItem>
#include <QPainter>

class Line : public QGraphicsItem
{
public:
    Line();
    void setAzimuth(const float azimuth);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QLineF* angleline;
};

#endif // LINE_H
