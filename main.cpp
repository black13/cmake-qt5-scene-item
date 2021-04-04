
#include <QApplication>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QMap>
#include <QTimer>


#include "scene.h"
#include "item.h"
int main(int argc, char** argv)
{

	QApplication app(argc, argv);

	Scene scene;
	scene.addItem(new Item(QColor(0xff, 0xff, 0xff),10.0,10.0));

	QGraphicsView view(&scene);
	view.show();
	
	return app.exec();
}
