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
#include <QApplication>
#include <QDesktopWidget>

/**
 * Constructor of block with operation.
 * @param x position ax
 * @param y position ay
 * @param parent view
 * @param operation operation of block
 * @param inputType type of input port values
 * @param outputType type of output port values
 */
Block::Block(const int x, const int y, BlockEditor* parent, QString operation, QString inputType, QString outputType) :
	parent(parent) {

	this->parent = parent;
	this->operation = operation;
	this->startBlock = false;
	this->blockType = BLOCK;

	// draw the block

	auto desktop = QApplication::desktop()->availableGeometry();

	setRect(x, y, 50 * (desktop.width() / 1920), 50 * (desktop.width() / 1920));

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);
	setBrush(brush);

	operationText = new QGraphicsTextItem(QString(operation), this);
	operationText->setFont(QFont("comic sans", 12));
	operationText->setPos(x + rect().width() / 2 - operationText->boundingRect().width() / 2,
				y + rect().height() / 2 - operationText->boundingRect().height() / 2);

	input.push_back(new BlockIO(x, y, INPUT, inputType, 0, parent, this));
	input.push_back(new BlockIO(x, y + 37 * (desktop.width() / 1920), INPUT, inputType, 0, parent, this));
	
	output.push_back(new BlockIO(x + 43 * (desktop.width() / 1920), y + 19 * (desktop.width() / 1920), OUTPUT, outputType, 0, parent, this));
	
	setIsPlaced(true);

	setZValue(0);

	// allow reposing to hover events
	setCursor(Qt::OpenHandCursor);
	setAcceptHoverEvents(true);
}

/**
 * Constructor of block with constant value.
 * @param x position ax
 * @param y position ay
 * @param parent view
 * @param value constant value
 * @param outputType type of output port values
 */
Block::Block(const int x, const int y, BlockEditor* parent, double value, QString outputType)
	: parent(parent) {

	this->parent = parent;
	this->operation = nullptr;
	this->startBlock = false;
	this->blockType = CONSTBLOCK;

	// draw the block
	auto desktop = QApplication::desktop()->availableGeometry();

	setRect(x, y, 50 * (desktop.width() / 1920), 50 * (desktop.width() / 1920));
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::yellow);
	setBrush(brush);

	operationText = new QGraphicsTextItem(QString::number(value), this);
	operationText->setFont(QFont("comic sans", 12));
	operationText->setPos(x + rect().width() / 2 - operationText->boundingRect().width() / 2,
		y + rect().height() / 2 - operationText->boundingRect().height() / 2);

	output.push_back(new BlockIO(x + 43 * (desktop.width() / 1920), y + 19 * (desktop.width() / 1920), OUTPUT, outputType, value, parent, this));

	setIsPlaced(true);

	setZValue(0);

	// allow reposing to hover events
	setCursor(Qt::OpenHandCursor);
	setAcceptHoverEvents(true);
}

/**
* Constructor of a result block.
* @param x position ax
* @param y position ay
* @param parent view
*/
Block::Block(const int x, const int y, BlockEditor* parent) :
	parent(parent) {

	this->parent = parent;
	this->operation = nullptr;
	this->startBlock = false;
	this->blockType = RESULT;

	// draw the block
	auto desktop = QApplication::desktop()->availableGeometry();

	setRect(x, y, 100 * (desktop.width() / 1920), 50 * (desktop.width() / 1920));
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::white);
	setBrush(brush);

	operationText = new QGraphicsTextItem("RESULT", this);
	operationText->setFont(QFont("comic sans", 12));
	operationText->setPos(x + rect().width() / 2 - operationText->boundingRect().width() / 2,
		y + rect().height() / 2 - operationText->boundingRect().height() / 2);

	input.push_back(new BlockIO(x, y + 19 * (desktop.width() / 1920), INPUT, nullptr, NULL, parent, this));

	setIsPlaced(true);

	setZValue(0);

	// allow reposing to hover events
	setCursor(Qt::OpenHandCursor);
	setAcceptHoverEvents(true);
}

/**
 * Pick up pressed block.
 * @param event graphics scene mouse event
 */
void Block::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	if (isPlaced()) { // block is placed
		if (event->button() == Qt::LeftButton && !parent->isDrawing()) {
			// pick up the block
			parent->pickUpBlock(this, event->pos());
		}
	}
}

/**
 * Place picked up block.
 * @param event graphics scene mouse event
 */
void Block::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	if (!isPlaced()) {
		if (event->button() == Qt::LeftButton) {
			parent->placeBlock(this);
		}
	}
}

/**
 * Get type of block.
 * @return type of block
 */
int Block::getBlockType() const { 
	return blockType; 
}


/**
 * Get wether block is placed.
 * @return placed block indicator
 */
bool Block::isPlaced() const {
	return placed;
};

/**
 * Get input ports of block.
 * @return input ports
 */
QVector<Block::BlockIO*> Block::getInputs() const {
	return input;
};

/**
 * Get output ports of block.
 * @return output ports
 */
QVector<Block::BlockIO*> Block::getOutputs() const {
	return output;
};

/**
 * Get block operation.
 * @return operation
 */
QString Block::getOperation() const {
	return operation;
};

/**
 * Get operation sign.
 * @return operation sign
 */
QGraphicsTextItem* Block::getOperationText() const {
	return operationText;
};


/**
 * Get wether current block is actual.
 * @return actual block indicator
 */
bool Block::isActualBlock() const {
	return startBlock;
};

/**
 * Set wether block is placed.
 * @param placed placed block indicator
 */
void Block::setIsPlaced(bool const placed) {
	this->placed = placed;
};

/**
 * Set operation of block.
 * @param operation operation
 */
void Block::setOperation(const QString operation) {
	this->operation = operation;
};

/**
 * Set operation sign.
 * @param operationText  operation sign
 */
void Block::setOperationText(QGraphicsTextItem* operationText) {
	this->operationText = operationText;
};

/**
 * Set block type.
 * @param blockType type of block
 */
void Block::setBlockType(const int blockType) {
	this->blockType = blockType;
};

/**
 * Set current block as actual.
 * @param startBlock actual block indicator
 */
void Block::setActualBlock(const bool startBlock) {
	this->startBlock = startBlock;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													BlockIO														  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Constructor of block's port.
 * @param x position in ax
 * @param y position in ay
 * @param IO type of port INPUT/OUTPUT
 * @param name type of port value
 * @param value value of port
 * @param editor view
 * @param parentBlock parent block
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

	auto desktop = QApplication::desktop()->availableGeometry();

	setRect(x, y, 50 * (desktop.width() / 1920), 50 * (desktop.width() / 1920));

	if (IO == INPUT) {
		setRect(x, y, 7 * (desktop.width() / 1920), 12 * (desktop.width() / 1920));
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
		setRect(x, y, 7 * (desktop.width() / 1920), 12 * (desktop.width() / 1920));
		setBrush(QBrush(QColor(Qt::blue)));
		setCursor(Qt::PointingHandCursor);
		cycle = false;
	}

	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);
}

/**
 * Set attributes of port.
 * @param line connection
 * @param isPoint1 first point of connection indicator
 */
void Block::BlockIO::addLine(Line* line, bool isPoint1) {
	this->line = line;
	isP1 = isPoint1;
	setCursor(Qt::ArrowCursor);
}

/**
 * Process item, which sent ItemScenePositionHasChanged
 * @param change item changed position indicator
 * @param value new position
 * @return new position of item
 */
QVariant Block::BlockIO::itemChange(GraphicsItemChange change, const QVariant &value) {
	if (line != nullptr && change == ItemScenePositionHasChanged && scene()) {
		// value is the new position.
		QPointF newPos = value.toPointF();

		moveLineToCenter(newPos);
	}
	return QGraphicsItem::itemChange(change, value);
}

/**
 * Set position of first point of connection in the middle of the
 * port.
 * @param newPos position of moved parent block
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

/**
 * Set connection to clicked port block
 * @param event graphics scene mouse event
 */
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
		QPointF newPoint(QCursor::pos().x(), QCursor::pos().y());
		newPoint = mapToScene(editor->getMousePos());
		Line* line = new Line(newPoint, newPoint, block->parent);
		editor->scene->addItem(line);
		addLine(line, true);
		line->setOutBlock(block);
		line->setOutPort(this);
		editor->setLine(line);
		editor->setLineStart(QCursor::pos());
		editor->setIsDrawing(true);
	}
}

/**
 * Show port name and value tooltip.
 * @param event graphics scene hover event
 */
void Block::BlockIO::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	setToolTip(getName() + ": " + QString::number(std::floor((getValue() * 100) + .5) / 100));
	if (!editor->isDrawing()) {
		QToolTip::showText(QCursor::pos(), toolTip());
	}
}

/**
 * Hide port name and value tooltip.
 * @param event graphics scene hover event
 */
void Block::BlockIO::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	if (!editor->isDrawing()) {
		QToolTip::hideText();
	}
}


/**
 * Set connection to a port.
 * @param line connection
 */
void Block::BlockIO::setLine(Line* line) {
	if (line == nullptr) {
		setCursor(Qt::PointingHandCursor);
	}
	this->line = line;
};

/**
 * Get port's conenction.
 * @return connection
 */
Line* Block::BlockIO::getLine() const
{
	return line;
};

/**
 * Get port name.
 * @return name
 */
QString Block::BlockIO::getName() const
{
	return name;
};

/**
 * Get port value.
 * @return value
 */
double Block::BlockIO::getValue() const
{
	return value;
};

/**
 * Get connection to port would create cycle indicator.
 * @return cycle indicator
 */
bool Block::BlockIO::isCycle() const
{
	return cycle;
};

/**
 * Port has value indicator.
 * @return port has value indicator
 */
bool Block::BlockIO::hasVal() const
{
	return hasValue;
};

/**
 * Set port name.
 * @param name name
 */
void Block::BlockIO::setName(const QString name)
{
	this->name = name;
};

/**
 * Set port value.
 * @param value value
 */
void Block::BlockIO::setValue(const double value)
{
	this->value = value; hasValue = true;
};

/**
 * Set connection to port would create cycle indicator.
 * @param cycle cycle indicator
 */
void Block::BlockIO::setCycle(const bool cycle)
{
	this->cycle = cycle;
};

/**
 * Set connectable indicator.
 * @param connectable connectable indicator
 */
void Block::BlockIO::setConnectable(const bool connectable)
{
	this->connectable = connectable;
};

/**
 * Set port has value indicator.
 * @param hasValue port has value indicator
 */
void Block::BlockIO::setHasVal(const bool hasValue)
{
	this->hasValue = hasValue;
};