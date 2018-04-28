#include "Block.h"
#include "BlockEditor.h"

#include <QGraphicsTextItem>
#include <QBrush>
#include <QDebug>

extern BlockEditor *blockEditor;

Block::Block(const int x, const int y, const int n, QGraphicsItem* parent) {
	// draw the block
	setRect(x, y, 50, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);
	setBrush(brush);

	QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(n), this);
	int const xPos = x + rect().width() / 2 - text->boundingRect().width() / 2;
	int const yPos = y + rect().height() / 2 - text->boundingRect().height() / 2;
	text->setPos(xPos, yPos);

	setIsPlaced(true);

	// allow reposing to hover events
	setAcceptHoverEvents(true);
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (isPlaced()) { // block is placed
		if (event->buttons() == Qt::LeftButton) {
			// pick up the block
			blockEditor->pickUpBlock(this, event->pos());
		}
	} else if (event->buttons() == Qt::LeftButton) { // place the block
		blockEditor->placeBlock(this);
	}
}