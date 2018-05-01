#pragma once

#include "Line.h"

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>

#define INPUT  1
#define OUTPUT 2


class BlockEditor;

class Block : public QGraphicsRectItem {

	public:
		// constructors
		Block(const int x, const int y, BlockEditor* parent, QString operation, int iPorts, int oPorts);

		// events
		void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

		BlockEditor *parent;

		class BlockIO : public QGraphicsRectItem {

			public:
				// constructors
				BlockIO(int x, int y, int IO, BlockEditor* editor, QGraphicsRectItem* parentBlock);

				// events
				void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

				// methods
				void addLine(Line *line, bool isPoint1);
				QVariant itemChange(GraphicsItemChange change, const QVariant &value);
				void moveLineToCenter(QPointF newPos);

				// getters
				QGraphicsLineItem* getLine() const { return line; };

				// setters
				void setLine(Line* line);

			private:
				// attributes
				QGraphicsRectItem* parentBlock;
				BlockEditor* editor;
				int IO;
				Line* line;
				bool isP1 = false;
		};

		// getters
		bool isPlaced() const { return placed; };
		QVector<BlockIO*> getInputs() const { return input; };
		QVector<BlockIO*> getOutputs() const { return output; };
		// setters
		void setIsPlaced(bool const placed) { this->placed = placed; };


	private:
		// attributes
		bool placed;
		QVector<BlockIO*> input;
		QVector<BlockIO*> output;
};

