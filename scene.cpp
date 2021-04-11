#include "scene.h"
#include "item.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "debug.h"

Scene::Scene(QObject *parent)
	: QGraphicsScene(parent)
{}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF mousePos(event->buttonDownScenePos(Qt::LeftButton).x(),
		event->buttonDownScenePos(Qt::LeftButton).y());
	const QList<QGraphicsItem *> itemList = items(mousePos);
	movingItem = itemList.isEmpty() ? nullptr : itemList.first();

	if (movingItem != nullptr && event->button() == Qt::LeftButton)
		oldPos = movingItem->pos();

	clearSelection();
	QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (movingItem != nullptr && event->button() == Qt::LeftButton) {
		if (oldPos != movingItem->pos())
			emit itemMoved(qgraphicsitem_cast<Item *>(movingItem),
				oldPos);
		movingItem = nullptr;
	}
	QGraphicsScene::mouseReleaseEvent(event);
}