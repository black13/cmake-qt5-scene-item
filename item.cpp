#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include "item.h"
#include "debug.h"

Item::Item(const QColor &color, int x, int y)
{
	trace_msg("");
	this->x = x;
	this->y = y;
	this->color = color;
	setZValue((x + y) % 2);

	setFlags(ItemIsSelectable | ItemIsMovable);
	setAcceptHoverEvents(true);
}

QRectF Item::boundingRect() const
{
	return QRectF(0, 0, 110, 70);
}

QPainterPath Item::shape() const
{
	trace_msg("");
	QPainterPath path;
	path.addRect(14, 14, 82, 42);
	return path;
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget);
	trace_msg("");
	QColor fillColor = (option->state & QStyle::State_Selected) ? color.darker(150) : color;
	if (option->state & QStyle::State_MouseOver)
		fillColor = fillColor.lighter(125);

	const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
	if (lod < 0.2) {
		if (lod < 0.125) {
			painter->fillRect(QRectF(100, 0, 110, 70), fillColor);
			return;
		}

		QBrush b = painter->brush();
		painter->setBrush(fillColor);
		painter->drawRect(13, 13, 97, 57);
		painter->setBrush(b);
		return;
	}

	QPen oldPen = painter->pen();
	QPen pen = oldPen;
	int width = 0;
	if (option->state & QStyle::State_Selected)
		width += 2;

	pen.setWidth(width);
	QBrush b = painter->brush();
	painter->setBrush(QBrush(fillColor.darker(option->state & QStyle::State_Sunken ? 120 : 100)));

	painter->drawRect(QRect(14, 14, 79, 39));
	painter->setBrush(b);

	if (lod >= 1) {
		painter->setPen(QPen(Qt::gray, 1));
		painter->drawLine(15, 54, 94, 54);
		painter->drawLine(94, 53, 94, 15);
		painter->setPen(QPen(Qt::black, 0));
	}

	// Draw text
	if (lod >= 2) {
		QFont font("Times", 10);
		font.setStyleStrategy(QFont::ForceOutline);
		painter->setFont(font);
		painter->save();
		painter->scale(0.1, 0.1);
		painter->drawText(170, 180, QString("Model: VSC-2000 (Very Small Item) at %1x%2").arg(x).arg(y));
		painter->drawText(170, 200, QString("Serial number: DLWR-WEER-123L-ZZ33-SDSJ"));
		painter->drawText(170, 220, QString("Manufacturer: Item Manufacturer"));
		painter->restore();
	}

	// Draw lines
	QVarLengthArray<QLineF, 36> lines;
	if (lod >= 0.5) {
		for (int i = 0; i <= 10; i += (lod > 0.5 ? 1 : 2)) {
			lines.append(QLineF(18 + 7 * i, 13, 18 + 7 * i, 5));
			lines.append(QLineF(18 + 7 * i, 54, 18 + 7 * i, 62));
		}
		for (int i = 0; i <= 6; i += (lod > 0.5 ? 1 : 2)) {
			lines.append(QLineF(5, 18 + i * 5, 13, 18 + i * 5));
			lines.append(QLineF(94, 18 + i * 5, 102, 18 + i * 5));
		}
	}
	if (lod >= 0.4) {
		const QLineF lineData[] = {
			QLineF(25, 35, 35, 35),
			QLineF(35, 30, 35, 40),
			QLineF(35, 30, 45, 35),
			QLineF(35, 40, 45, 35),
			QLineF(45, 30, 45, 40),
			QLineF(45, 35, 55, 35)
		};
		lines.append(lineData, 6);
	}
	painter->drawLines(lines.data(), lines.size());

	// Draw red ink
	if (stuff.size() > 1) {
		QPen p = painter->pen();
		painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter->setBrush(Qt::NoBrush);
		QPainterPath path;
		path.moveTo(stuff.first());
		for (int i = 1; i < stuff.size(); ++i)
			path.lineTo(stuff.at(i));
		painter->drawPath(path);
		painter->setPen(p);
	}
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	trace_msg("");
	QGraphicsItem::mousePressEvent(event);
	update();
}

void Item::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	trace_msg("");
	if (event->modifiers() & Qt::ShiftModifier) {
		stuff << event->pos();
		update();
		return;
	}
	QGraphicsItem::mouseMoveEvent(event);
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	trace_msg("");
	QGraphicsItem::mouseReleaseEvent(event);
	update();
}
