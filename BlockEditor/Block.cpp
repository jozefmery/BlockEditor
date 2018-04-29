#include "Block.h"
#include "BlockEditor.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

extern BlockEditor *blockEditor;

Block::Block(const int x, const int y, QGraphicsItem* parent) {
	//setFlag(QGraphicsItem::ItemIsMovable);
	//setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

	// draw the block
	setRect(x, y, 50, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);
	setBrush(brush);

	setIsPlaced(true);

	// allow reposing to hover events
	setCursor(Qt::OpenHandCursor);
	setAcceptHoverEvents(true);
}

void Block::addLine(QGraphicsLineItem *line, bool isPoint1) {
	this->line = line;
	isP1 = isPoint1;
}

QVariant Block::itemChange(GraphicsItemChange change, const QVariant &value) {
	if (change == ItemPositionChange && scene()) {
		// value is the new position.
		QPointF newPos = value.toPointF();

		moveLineToCenter(newPos);
	}
	return QGraphicsItem::itemChange(change, value);
}

void Block::moveLineToCenter(QPointF newPos) {
	// Converts the elipse position (top-left)
	// to its center position
	int xOffset = rect().x() + rect().width() / 2;
	int yOffset = rect().y() + rect().height() / 2;

	QPointF newCenterPos = QPointF(newPos.x() + xOffset, newPos.y() + yOffset);

	// Move the required point of the line to the center of the elipse
	QPointF p1 = isP1 ? newCenterPos : line->line().p1();
	QPointF p2 = isP1 ? line->line().p2() : newCenterPos;

	line->setLine(QLineF(p1, p2));
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (isPlaced()) { // block is placed
		if (event->buttons() == Qt::LeftButton) {
			// pick up the block
			blockEditor->pickUpBlock(this, event->pos());
		}
	} else {
		if (event->buttons() == Qt::LeftButton) { // place the block
			blockEditor->placeBlock(this);
		} else if (event->buttons() == Qt::RightButton) {
			// TODO: blockEditor->rotateBlock(this);
		}
	}
}