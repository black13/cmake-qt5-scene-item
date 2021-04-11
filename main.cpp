
#include <QApplication>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QMap>
#include <QTimer>
#include <QRectF>

#include "scene.h"
#include "item.h"
#include "view.h"
int main(int argc, char** argv)
{

	QApplication app(argc, argv);

	Scene scene;
	//scene.addItem(new Item(QColor(0xff, 0xff, 0xff),10.0,10.0));

	//QGraphicsRectItem *item = scene.addRect(QRectF(0.0,0.0,10.0, 10.0));
	//item->setFlag(QGraphicsItem::ItemIsMovable);
	//item->setFlag(QGraphicsItem::ItemIsSelectable);
	View view(&scene);
	view.show();
	
	return app.exec();
}
