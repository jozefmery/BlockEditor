#include "Block.h"
#include "BlockEditor.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QCursor>
#include <QDebug>

//extern BlockEditor *blockEditor;

Block::Block(const int x, const int y, BlockEditor* parent, QString operation, QString inputType, QString outputType) :
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


	if (operation == "+" || operation == "-") {
		input.push_back(new BlockIO(x, y, INPUT, inputType, 0, parent, this));
		input.push_back(new BlockIO(x, y + 37, INPUT, inputType, 0, parent, this));
	} else if (operation == "*" || operation == "/") {
		input.push_back(new BlockIO(x, y, INPUT, inputType, 1, parent, this));
		input.push_back(new BlockIO(x, y + 37, INPUT, inputType, 1, parent, this));
	}
	
	output.push_back(new BlockIO(x + 43, y + 19, OUTPUT, outputType, 0, parent, this));
	
	setIsPlaced(true);

	setZValue(0);

	// allow reposing to hover events
	setCursor(Qt::OpenHandCursor);
	setAcceptHoverEvents(true);
}

Block::Block(const int x, const int y, BlockEditor* parent, double value, QString outputType)
	: parent(parent) {

	this->parent = parent;

	// draw the block
	setRect(x, y, 50, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::yellow);
	setBrush(brush);

	QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(value), this);
	text->setFont(QFont("comic sans", 7));
	text->setPos(x + rect().width() / 2 - text->boundingRect().width() / 2,
		y + rect().width() / 2 - text->boundingRect().height() / 2);

	output.push_back(new BlockIO(x + 43, y + 19, OUTPUT, outputType, value, parent, this));

	setIsPlaced(true);

	setZValue(0);

	// allow reposing to hover events
	setCursor(Qt::OpenHandCursor);
	setAcceptHoverEvents(true);
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (isPlaced()) { // block is placed
		if (event->button() == Qt::LeftButton && !parent->isDrawing()) {
			// pick up the block
			parent->pickUpBlock(this, event->pos());
		}
	}
}

void Block::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	if (!isPlaced()) {
		if (event->button() == Qt::LeftButton) {
			parent->placeBlock(this);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													BlockIO														  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Block::BlockIO::BlockIO(int x, int y, int IO, QString name, double value, BlockEditor* editor, QGraphicsRectItem* parentBlock) : QGraphicsRectItem(parentBlock) {

	setFlag(ItemSendsScenePositionChanges);

	this->IO = IO;
	this->editor = editor;
	this->parentBlock = parentBlock;
	this->name = name;
	this->value = value;
	line = nullptr;

	if (IO == INPUT) {
		setRect(x, y, 6, 12);
		setBrush(QBrush(QColor(Qt::green)));
		setCursor(Qt::ArrowCursor);
	}
	else if (IO == OUTPUT) {
		setRect(x, y, 6, 12);
		setBrush(QBrush(QColor(Qt::blue)));
		setCursor(Qt::PointingHandCursor);
	}

	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);
}

void Block::BlockIO::addLine(Line* line, bool isPoint1) {
	this->line = line;
	isP1 = isPoint1;
	setCursor(Qt::ArrowCursor);
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
	Block* block = dynamic_cast<Block*>(parentBlock);
	if (IO == INPUT && editor->isDrawing() && line == nullptr) {
		if (editor->getLine()->getOutBlock() != block) {
			Line *line = editor->getLine();
			line->setInBlock(block);
			editor->setIsDrawing(false);
			addLine(line, false);
		}
	} else if (IO == OUTPUT && !editor->isDrawing() && line == nullptr) {
		Line* line = new Line(event->pos(), event->pos(), block->parent);
		editor->scene->addItem(line);
		addLine(line, true);
		line->setOutBlock(block);
		editor->setLine(line);
		editor->setLineStart(QCursor::pos());
		editor->setIsDrawing(true);
	}
}

void Block::BlockIO::setLine(Line* line) {
	if (line == nullptr) {
		setCursor(Qt::PointingHandCursor);
	}
	this->line = line;
};


