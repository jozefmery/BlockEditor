#include "Line.h"
#include "Block.h"
#include "BlockEditor.h"

#include <QPen>
#include <QToolTip>
#include <QCursor>

Line::Line(QPointF p1, QPointF p2, BlockEditor* parent) : parent(parent) {

	this->parent = parent;

	QPen pen;
	pen.setWidth(3);
	setPen(pen);

	setAcceptHoverEvents(true);

	setToolTip("Nothing");
}

void Line::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	if (!parent->isDrawing()) {
		QToolTip::showText(QCursor::pos(), toolTip());
	}
}

void Line::hoverMoveEvent(QGraphicsSceneHoverEvent* event) {
	// vobec neviem na co mi to je ale mozno niekedy to pouzijem
}

void Line::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	if (!parent->isDrawing()) {
		QToolTip::hideText();
	}
}

Block* Line::getOutBlock() const { return outBlock; };
Block* Line::getInBlock() const { return inBlock; };

void Line::setOutBlock(Block* outBlock) { this->outBlock = outBlock; };
void Line::setInBlock(Block* inBlock) { this->inBlock = inBlock; };