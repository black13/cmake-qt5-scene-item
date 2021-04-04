
#include <QApplication>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QMap>
#include <QTimer>
;

int main(int argc, char** argv)
{

	QApplication app(argc, argv);

	QGraphicsScene scene;
	scene.addText("Hello, world!");

	QGraphicsView view(&scene);
	view.show();
	
	return app.exec();
}
