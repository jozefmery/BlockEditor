#include "Line.h"
#include "BlockEditor.h"

#include <QPen>
#include <QToolTip>
#include <QCursor>

/**
 * Constructor
 * @param p1 first point of a connection
 * @param p2 second point of a connection
 * @param parent view
 */
Line::Line(QPointF p1, QPointF p2, BlockEditor* parent) : parent(parent) {

	QPen pen;
	pen.setWidth(3);
	setPen(pen);

	setAcceptHoverEvents(true);

	setToolTip("Nothing");
}

/**
 * Show connection tooltip.
 * @param event graphics scene hover event
 */
void Line::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	if (!parent->isDrawing()) {
		QToolTip::showText(QCursor::pos(), toolTip());
	}
}

/**
* Hide connection tooltip.
* @param event graphics scene hover event
*/
void Line::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	if (!parent->isDrawing()) {
		QToolTip::hideText();
	}
}

/**
 * Get output block.
 * @return output block
 */
Block* Line::getOutBlock() const {
	return outBlock;
}

/**
 * Get input block.
 * @return input block
 */
Block* Line::getInBlock() const {
	return inBlock;
}

/**
 * Set output block.
 * @param outBlock output block
 */
void Line::setOutBlock(Block* outBlock) {
	this->outBlock = outBlock;
}

/**
 * Set input block.
 * @param inBlock input block
 */
void Line::setInBlock(Block* inBlock) {
	this->inBlock = inBlock;
}

/**
 * Get input port.
 * @return input port
 */
Block::BlockIO* Line::getInPort() const {
	return input;
}

/**
 * Get output port.
 * @return output port
 */
Block::BlockIO* Line::getOutPort() const {
	return output;
}

/**
 * Set input port.
 * @param input input port
 */
void Line::setInPort(Block::BlockIO* input) {
	this->input = input;
}

/**
 * Set output port.
 * @param output output port
 */
void Line::setOutPort(Block::BlockIO* output) {
	this->output = output;
}