#ifndef RECT_H
#define RECT_H

#include <QGraphicsRectItem>

class Rect : public QGraphicsRectItem {
public:
	Rect(qreal y, qreal width, qreal height, QColor color,
		QGraphicsItem *parent = nullptr);

public:
	QPainterPath shape() const override;
};

#endif  //RECT_H