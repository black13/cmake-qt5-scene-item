#ifndef ITEM_H__
#define ITEM_H__

#include <QColor>
#include <QGraphicsItem>

class Item : public QGraphicsItem
{
public:
	Item(const QColor &color, int x, int y);

	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
	int x;
	int y;
	QColor color;
	QVector<QPointF> stuff;
};


#endif