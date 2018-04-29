#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>

class BlockEditor;

class Block : public QGraphicsRectItem {

	public:
		// constructors
		Block(const int x, const int y, BlockEditor* parent);

		// events
		void Block::mousePressEvent(QGraphicsSceneMouseEvent* event);

		// getters
		inline bool isPlaced() const { return placed; }
		// setters
		inline void setIsPlaced(bool const placed) { this->placed = placed; }

		BlockEditor *parent;

		// methods
		void addLine(QGraphicsLineItem *line, bool isPoint1);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);
		void moveLineToCenter(QPointF newPos);

	private:
		// attributes
		QGraphicsLineItem * line;
		bool isP1;
		bool placed;
};

