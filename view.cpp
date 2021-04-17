
#include "view.h"
#include "scene.h"
#include <math.h>
#include "item.h"
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QMenu>
#include <QDebug>

View::View(QGraphicsScene *scene,QWidget *parent)
    : QGraphicsView(scene,parent)
{
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
}



void View::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}


void View::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}


//https://stackoverflow.com/questions/14389058/is-there-a-way-to-know-what-activated-qaction
//https://stackoverflow.com/questions/50134082/get-qgraphicsitem-by-mouse-position-in-qgraphicsscene
void View::contextMenuEvent(QContextMenuEvent *event)
{
	Scene  *scenpt = dynamic_cast<Scene*>(this->scene());
	QTransform transform;
	auto ret = mapToScene(event->pos());
	QPointF scenePos = mapToScene(event->pos());
	QPoint globalPos = mapToGlobal(event->pos());
	QMenu menu;
	QAction* addAction = menu.addAction("Add", this, &View::addAction);
	addAction->setData(scenePos);
	menu.exec(event->globalPos());
}

void View::addAction()
{
	QAction* pAction = qobject_cast<QAction*>(sender());
	Q_ASSERT(pAction);

	QPointF ret = pAction->data().toPointF();

	Scene  *scenpt = dynamic_cast<Scene*>(this->scene());
	//scenpt->addRect(QRectF(QPointF(0.0, 0.0), ret));
	//qDebug() << ret.x() << "," << ret.y(); 
	//scenpt->addItem(new Item(QColor(0xff, 0xff, 0xff),0.0,0.0));
	QGraphicsRectItem *item = scenpt->addRect(QRectF(ret.x(), ret.y(), 20, 20));
	item->setFlag(QGraphicsItem::ItemIsMovable);
	item->setFlag(QGraphicsItem::ItemIsSelectable);
}


/*
#include <QGraphicsItem>
QGraphicsRectItem *item = scenpt->addRect(QRectF(QPointF(0.0, 0.0), ret));
item->setFlag(QGraphicsItem::ItemIsMovable);
item->setFlag(QGraphicsItem::ItemIsSelectable);
*/