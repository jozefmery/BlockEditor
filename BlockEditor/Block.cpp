#include "Block.h"
#include "BlockEditor.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QBrush>
#include <QCursor>
#include <QDebug>
#include <QWidget>

//extern BlockEditor *blockEditor;

Block::Block(const int x, const int y, BlockEditor* parent) :
	parent(parent) {

	this->parent = parent;

	// draw the block
	setRect(x, y, 50, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);
	setBrush(brush);

	BlockIO* input = new BlockIO(x, y, INPUT, parent, this);
	BlockIO* output = new BlockIO(x, y, OUTPUT, parent, this);

	setIsPlaced(true);

	// allow reposing to hover events
	setCursor(Qt::OpenHandCursor);
	setAcceptHoverEvents(true);
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (isPlaced()) { // block is placed
		if (event->buttons() == Qt::LeftButton) {
			// pick up the block
			parent->pickUpBlock(this, event->pos());
		}
	} else {
		if (event->buttons() == Qt::LeftButton) { // place the block
			parent->placeBlock(this);
		} else if (event->buttons() == Qt::RightButton) {
			// TODO: blockEditor->rotateBlock(this);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													BlockIO														  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Block::BlockIO::BlockIO(int x, int y, int IO, BlockEditor* editor, QGraphicsRectItem* parentBlock) : QGraphicsRectItem(parentBlock) {

	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

	this->IO = IO;
	this->editor = editor;
	this->parentBlock = parentBlock;
	line = nullptr;

	if (IO == INPUT) {
		setRect(x + 2, y + 37, 13, 13);
		setBrush(QBrush(QColor(Qt::green)));
	}
	else if (IO == OUTPUT) {
		setRect(x + 35, y + 37, 13, 13);
		setBrush(QBrush(QColor(Qt::blue)));
	}

	setCursor(Qt::PointingHandCursor);
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);
}

void Block::BlockIO::addLine(QGraphicsLineItem *line, bool isPoint1) {
	this->line = line;
	isP1 = isPoint1;
}

QVariant Block::BlockIO::itemChange(GraphicsItemChange change, const QVariant &value) {
	if (line != nullptr && change == ItemScenePositionHasChanged && scene()) {
		// value is the new position.
		QPointF newPos = value.toPointF();

		moveLineToCenter(newPos);
	}
	return QGraphicsItem::itemChange(change, value);
}

void Block::BlockIO::moveLineToCenter(QPointF newPos) {
	// Converts the port position to its center position
	int xOffset = rect().x() + rect().width() / 2;
	int yOffset = rect().y() + rect().height() / 2;

	QPointF newCenterPos = QPointF(newPos.x() + xOffset, newPos.y() + yOffset);

	// Move the required point of the line to the center of the elipse
	QPointF p1 = isP1 ? newCenterPos : line->line().p1();
	QPointF p2 = isP1 ? line->line().p2() : newCenterPos;

	line->setLine(QLineF(p1, p2));
}

void Block::BlockIO::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (IO == INPUT && editor->isDrawing()) {
		QGraphicsLineItem *line = editor->getLine();
		editor->setIsDrawing(false);
		addLine(line, false);
	}
	else if (IO == OUTPUT && !editor->isDrawing()) {
		QGraphicsLineItem *line = editor->scene->addLine(QLineF(event->pos(), event->pos()));
		addLine(line, true);
		editor->setIsDrawing(true);
		editor->setLine(line);
		editor->setLineStart(QCursor::pos());
	}
}
