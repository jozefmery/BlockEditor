#include "Block.h"
#include "BlockEditor.h"

#include <QGraphicsTextItem>
#include <QBrush>

Block::Block(const int x, const int y, QGraphicsItem* parent) {
	// draw the block
	setRect(x, y, 50, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);
	setBrush(brush);

	setIsPlaced(true);

	// allow reposing to hover events
	setAcceptHoverEvents(true);
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (isPlaced()) { // block is placed
		if (event->buttons() == Qt::LeftButton) {
			// pick up the block
			parent->pickUpBlock(this, event->pos());
		}
	} else if (event->buttons() == Qt::LeftButton) { // place the block
		parent->placeBlock(this);
	}
}