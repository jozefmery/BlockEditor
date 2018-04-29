#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>

class Block : public QGraphicsRectItem {

	public:
		// constructors
		Block(const int x, const int y, QGraphicsItem* parent = nullptr);

		// events
		void Block::mousePressEvent(QGraphicsSceneMouseEvent* event);

		// getters
		inline bool isPlaced() const { return placed; };
		// setters
		inline void setIsPlaced(bool const placed) { this->placed = placed; };

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

