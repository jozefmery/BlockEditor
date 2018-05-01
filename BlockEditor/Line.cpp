#include "Line.h"

#include <QPen>
#include <QToolTip>
#include <QCursor>

Line::Line(QPointF p1, QPointF p2) {

	QPen pen;
	pen.setWidth(3);
	setPen(pen);

	setAcceptHoverEvents(true);

	setToolTip("Nothing");
}

void Line::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	QToolTip::showText(QCursor::pos(), toolTip());	
}

void Line::hoverMoveEvent(QGraphicsSceneHoverEvent* event) {
	
}

void Line::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	QToolTip::hideText();
}

void Line::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (event->button() == Qt::RightButton) {
		
	}
}