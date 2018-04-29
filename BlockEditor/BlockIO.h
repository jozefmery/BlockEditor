#pragma once

//#include "Block.h"
#include "BlockEditor.h"

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>

#define INPUT  1
#define OUTPUT 2

class BlockIO: public QGraphicsRectItem {

	public:
		// constructors
		BlockIO(int x, int y, int IO, BlockEditor* editor, QGraphicsRectItem* parentBlock);

		// events
		void mousePressEvent(QGraphicsSceneMouseEvent* event);

		// methods
		void addLine(QGraphicsLineItem *line, bool isPoint1);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);
		void moveLineToCenter(QPointF newPos);

		// getters

		// setters

	private:
		// attributes
		QGraphicsRectItem * parentBlock;
		BlockEditor* editor;
		int IO;
		QGraphicsLineItem* line;
		bool isP1 = false;
};

