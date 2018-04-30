#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>

#define INPUT  1
#define OUTPUT 2


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

		class BlockIO : public QGraphicsRectItem {

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


	private:
		// attributes
		bool placed;
};

