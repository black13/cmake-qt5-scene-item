
#ifndef NODESCENE_H
#define NODESCENE_H

#include <QGraphicsScene>
#include <QMultiMap>
#include <QSet>
#include <QHash>

class Item;
class QGraphicsRectItem;
//class Line;
class Scene : public QGraphicsScene
{
	Q_OBJECT

public:
	Scene(QObject *parent = nullptr);

signals:
	void itemMoved(Item *movedItem, const QPointF &movedFromPosition);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
	QGraphicsItem *movingItem = nullptr;
	QPointF oldPos;
	QHash<QGraphicsRectItem*, QSet<QGraphicsRectItem*>> m_graph;
};

#endif // NODESCENE_H
