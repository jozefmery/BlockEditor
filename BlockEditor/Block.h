#pragma once

#include <QGraphicsRectItem>

class BlockEditor;

class Block : public QGraphicsRectItem {

	public:
		// constructors
		Block(const int x, const int y, BlockEditor* parent);

		// events
		void mousePressEvent(QGraphicsSceneMouseEvent* event);

		// getters
		inline bool isPlaced() const { return placed; };
		// setters
		inline void setIsPlaced(bool const placed) { this->placed = placed; };

		BlockEditor *parent;

	private:
		// attributes
		bool placed;
};

