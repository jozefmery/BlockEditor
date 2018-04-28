#pragma once

#include <QVector>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Block : public QGraphicsRectItem {

	public:
		// constructors
		Block(int x, int y, int n, QGraphicsItem* parent = NULL);

		// events
		void Block::mousePressEvent(QGraphicsSceneMouseEvent* event);

		// getters
		inline bool isPlaced() const { return placed; };
		// setters
		inline void setIsPlaced(bool const placed) { this->placed = placed; };

	private:
		// attributes
		bool placed;

};

