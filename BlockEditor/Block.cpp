#include "Block.h"
#include "Line.h"
#include "BlockEditor.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QCursor>
#include <QDebug>
#include <QTextDocument>
#include <cmath>
#include <QToolTip>

/**
 * \brief Constructor of block with operation.
 * \param x position ax
 * \param y position ay
 * \param parent view
 * \param operation operation of block
 * \param inputType type of input port values
 * \param outputType type of output port values
 */
Block::Block(const int x, const int y, BlockEditor* parent, QString operation, QString inputType, QString outputType) :
	parent(parent) {

	this->parent = parent;
	this->operation = operation;
	this->startBlock = false;

	setBlockType(BLOCK);

	// draw the block
	setRect(x, y, 50, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);
	setBrush(brush);

	operationText = new QGraphicsTextItem(QString(operation), this);
	operationText->setFont(QFont("comic sans", 10));
	operationText->setPos(x + rect().width() / 2 - operationText->boundingRect().width() / 2,
				y + rect().height() / 2 - operationText->boundingRect().height() / 2);

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

/**
 * \brief Constructor of block with constant value.
 * \param x position ax
 * \param y position ay
 * \param parent view
 * \param value constant value
 * \param outputType type of output port values
 */
Block::Block(const int x, const int y, BlockEditor* parent, double value, QString outputType)
	: parent(parent) {

	this->parent = parent;
	this->operation = nullptr;
	this->startBlock = false;

	setBlockType(CONSTBLOCK);

	// draw the block
	setRect(x, y, 50, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::yellow);
	setBrush(brush);

	operationText = new QGraphicsTextItem(QString::number(value), this);
	operationText->setFont(QFont("comic sans", 7));
	operationText->setPos(x + rect().width() / 2 - operationText->boundingRect().width() / 2,
		y + rect().height() / 2 - operationText->boundingRect().height() / 2);

	output.push_back(new BlockIO(x + 43, y + 19, OUTPUT, outputType, value, parent, this));

	setIsPlaced(true);

	setZValue(0);

	// allow reposing to hover events
	setCursor(Qt::OpenHandCursor);
	setAcceptHoverEvents(true);
}

/**
* \brief Constructor of a result block.
* \param x position ax
* \param y position ay
* \param parent view
*/
Block::Block(const int x, const int y, BlockEditor* parent) :
	parent(parent) {

	this->parent = parent;
	this->operation = nullptr;
	this->startBlock = false;

	setBlockType(RESULT);

	// draw the block
	setRect(x, y, 60, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::white);
	setBrush(brush);

	operationText = new QGraphicsTextItem(this);
	operationText->setPos(x + rect().width() / 2, y + rect().height() / 2);

	input.push_back(new BlockIO(x, y + 19, INPUT, nullptr, NULL, parent, this));

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

/**
 * \brief Constructor of block's port.
 * \param x position in ax
 * \param y position in ay
 * \param IO type of port INPUT/OUTPUT
 * \param name type of port value
 * \param value value of port
 * \param editor view
 * \param parentBlock parent block
 */
Block::BlockIO::BlockIO(int x, int y, int IO, QString name, double value, BlockEditor* editor, QGraphicsRectItem* parentBlock) : QGraphicsRectItem(parentBlock) {

	setFlag(ItemSendsScenePositionChanges);

	this->IO = IO;
	this->editor = editor;
	this->parentBlock = parentBlock;
	this->name = name;
	this->value = value;
	this->connectable = true;
	this->hasValue = false;

	line = nullptr;

	if (IO == INPUT) {
		setRect(x, y, 7, 12);
		if (dynamic_cast<Block*>(parentBlock)->getBlockType() == RESULT) {
			setBrush(QBrush(QColor(Qt::green)));
		} else {
			setBrush(QBrush(QColor(Qt::white)));
		}
		setCursor(Qt::ArrowCursor);
		cycle = false;
	}
	else if (IO == OUTPUT) {
		if (dynamic_cast<Block*>(parentBlock)->getBlockType() == CONSTBLOCK) {
			this->hasValue = true;
		}
		setRect(x, y, 7, 12);
		setBrush(QBrush(QColor(Qt::blue)));
		setCursor(Qt::PointingHandCursor);
		cycle = false;
	}

	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);
}

/**
 * \brief Set attributes of port.
 * \param line connection
 * \param isPoint1 first point of connection indicator
 */
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

/**
 * \brief Set position of first point of connection in the middle of the
 * port.
 * \param newPos position of moved parent block
 */
void Block::BlockIO::moveLineToCenter(QPointF newPos) {
	// Converts the port position to its center position
	const int xOffset = rect().x() + rect().width() / 2;
	const int yOffset = rect().y() + rect().height() / 2;

	const QPointF newCenterPos = QPointF(newPos.x() + xOffset, newPos.y() + yOffset);

	// Move the required point of the line to the center of the port
	QPointF p1 = isP1 ? newCenterPos : line->line().p1();
	QPointF p2 = isP1 ? line->line().p2() : newCenterPos;

	line->setLine(QLineF(p1, p2));
	line->setZValue(2);
}

void Block::BlockIO::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	Block* block = dynamic_cast<Block*>(parentBlock);
	if (IO == INPUT && editor->isDrawing() && line == nullptr) {
		if (editor->getLine()->getOutBlock() != block && connectable) {
			Line *line = editor->getLine();
			line->setInBlock(block);
			line->setInPort(this);
			editor->setIsDrawing(false);
			addLine(line, false);
		}
	} else if (IO == OUTPUT && !editor->isDrawing() && line == nullptr) {
		Line* line = new Line(event->pos(), event->pos(), block->parent);
		editor->scene->addItem(line);
		addLine(line, true);
		line->setOutBlock(block);
		line->setOutPort(this);
		editor->setLine(line);
		editor->setLineStart(QCursor::pos());
		editor->setIsDrawing(true);
	}
}

void Block::BlockIO::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	setToolTip(getName() + ": " + QString::number(std::floor((getValue() * 100) + .5) / 100));
	if (!editor->isDrawing()) {
		QToolTip::showText(QCursor::pos(), toolTip());
	}
}

void Block::BlockIO::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	if (!editor->isDrawing()) {
		QToolTip::hideText();
	}
}


void Block::BlockIO::setLine(Line* line) {
	if (line == nullptr) {
		setCursor(Qt::PointingHandCursor);
	}
	this->line = line;
};


