#include "BlockIO.h"

#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QCursor>
#include <QDebug>
#include <QWidget>

BlockIO::BlockIO(int x, int y, int IO, BlockEditor* editor, QGraphicsRectItem* parentBlock) : QGraphicsRectItem(parentBlock) {
	
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

	this->IO = IO;
	this->editor = editor;
	this->parentBlock = parentBlock;

	if (IO == INPUT) {
		setRect(x + 2, y + 37, 13, 13);
		setBrush(QBrush(QColor(Qt::green)));
	} else if (IO == OUTPUT) {
		setRect(x + 35, y + 37, 13, 13);
		setBrush(QBrush(QColor(Qt::blue)));
	}

	setCursor(Qt::PointingHandCursor);
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);
}

void BlockIO::addLine(QGraphicsLineItem *line, bool isPoint1) {
	this->line = line;
	isP1 = isPoint1;
}

QVariant BlockIO::itemChange(GraphicsItemChange change, const QVariant &value) {
	if (change == ItemPositionChange && scene()) {
		// value is the new position.
		QPointF newPos = value.toPointF();

		moveLineToCenter(newPos);
	}
	return QGraphicsItem::itemChange(change, value);
}

void BlockIO::moveLineToCenter(QPointF newPos) {
	// Converts the port position to its center position
	int xOffset = rect().x() + rect().width() / 2;
	int yOffset = rect().y() + rect().height() / 2;

	QPointF newCenterPos = QPointF(newPos.x() + xOffset, newPos.y() + yOffset);

	// Move the required point of the line to the center of the elipse
	QPointF p1 = isP1 ? newCenterPos : line->line().p1();
	QPointF p2 = isP1 ? line->line().p2() : newCenterPos;

	line->setLine(QLineF(p1, p2));
}

void BlockIO::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (IO == INPUT && editor->isDrawing()) {
		QGraphicsLineItem *line = editor->getLine();
		editor->setIsDrawing(false);
		addLine(line, false);
	} else if (IO == OUTPUT && !editor->isDrawing()) {
		QGraphicsLineItem *line = editor->scene->addLine(QLineF(event->pos(), event->pos()));
		addLine(line, true);
		editor->setIsDrawing(true);
		editor->setLine(line);
		editor->setLineStart(QCursor::pos());
	}
}