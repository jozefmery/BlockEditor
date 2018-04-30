#include "Block.h"
#include "BlockEditor.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QBrush>
#include <QCursor>
#include <QDebug>
#include <QWidget>
#include <qfutureinterface.h>

//extern BlockEditor *blockEditor;

Block::Block(const int x, const int y, BlockEditor* parent, QString operation, int iPorts, int oPorts) :
	parent(parent) {

	this->parent = parent;

	// draw the block
	setRect(x, y, 50, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);
	setBrush(brush);

	QGraphicsTextItem* text = new QGraphicsTextItem(QString(operation), this);
	text->setFont(QFont("comic sans", 10));
	text->setPos(x + rect().width() / 2 - text->boundingRect().width() / 2,
				y + rect().width() / 2 - text->boundingRect().height() / 2);

	if (iPorts == 1) {
		input.push_back(new BlockIO(x, y + 37, INPUT, parent, this));
	} else {
		input.push_back(new BlockIO(x, y, INPUT, parent, this));
		input.push_back(new BlockIO(x, y + 37, INPUT, parent, this));
	}
	
	if (oPorts == 1) {
		input.push_back(new BlockIO(x + 37, y + 37, OUTPUT, parent, this));
	}
	else {
		input.push_back(new BlockIO(x + 37, y, OUTPUT, parent, this));
		input.push_back(new BlockIO(x + 37, y + 37, OUTPUT, parent, this));
	}

	setIsPlaced(true);

	setZValue(0);

	// allow reposing to hover events
	setCursor(Qt::OpenHandCursor);
	setAcceptHoverEvents(true);
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (isPlaced()) { // block is placed
		if (event->buttons() == Qt::LeftButton && !parent->isDrawing()) {
			// pick up the block
			parent->pickUpBlock(this, event->pos());
		}
	} else {
		if (event->buttons() == Qt::LeftButton) { // place the block
			parent->placeBlock(this);
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
		setRect(x, y, 13, 13);
		setBrush(QBrush(QColor(Qt::green)));
	}
	else if (IO == OUTPUT) {
		setRect(x, y, 13, 13);
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

	// Move the required point of the line to the center of the port
	QPointF p1 = isP1 ? newCenterPos : line->line().p1();
	QPointF p2 = isP1 ? line->line().p2() : newCenterPos;

	line->setLine(QLineF(p1, p2));
	line->setZValue(2);
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
