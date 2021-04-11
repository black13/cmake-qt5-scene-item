

#ifndef VIEW_H__
#define VIEW_H__

#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT

public:
	View(QGraphicsScene *scene, QWidget *parent = nullptr);

    void itemMoved();

public slots:
   // void shuffle();


protected:


    void scaleView(qreal scaleFactor);

private:
    int timerId = 0;

};
//! [0]

#endif // VIEW_H__
