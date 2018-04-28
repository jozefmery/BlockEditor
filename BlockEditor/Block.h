#pragma once

#include <QGraphicsRectItem>

class Block : public QGraphicsRectItem {

	public:
		// constructors
		Block(const int x, const int y, const int n, QGraphicsItem* parent = nullptr);

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

