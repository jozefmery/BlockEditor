#include "BlockSpawner.h"

#include <QGraphicsTextItem>
#include <QBrush>

BlockSpawner::BlockSpawner() {
	// draw the rect
	setRect(0, 0, 200, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::gray);
	setBrush(brush);

	// set text
	QGraphicsTextItem* text = new QGraphicsTextItem("Block Spawner", this);
	int xPos = rect().width() / 2 - text->boundingRect().width() / 2;
	int yPos = rect().height() / 2 - text->boundingRect().height() / 2;
	text->setPos(xPos, yPos);

	// allow reposing to hover events
	setAcceptHoverEvents(true);

	blockOrder = 1;
}

void BlockSpawner::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	emit clicked();
}

void BlockSpawner::mouseHoverEvent(QGraphicsSceneHoverEvent* event) {
	// TODO: imitacia kliknutia na tlacidlo ak bude cas alebo nejaka uprava
}

void BlockSpawner::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	// TODO: imitacia kliknutia na tlacidlo ak bude cas alebo nejaka uprava
}