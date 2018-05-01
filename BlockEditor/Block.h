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

		BlockEditor *parent;

		class BlockIO : public QGraphicsRectItem {

			public:
				// constructors
				BlockIO(int x, int y, int IO, BlockEditor* editor, QGraphicsRectItem* parentBlock);

				// events
				void mousePressEvent(QGraphicsSceneMouseEvent* event);

				// methods
				void addLine(Line *line, bool isPoint1);
				QVariant itemChange(GraphicsItemChange change, const QVariant &value);
				void moveLineToCenter(QPointF newPos);

				// getters
				inline QGraphicsLineItem* getLine() const { return line; };

				// setters
				inline void setLine(Line* line) { this->line = line; };

			private:
				// attributes
				QGraphicsRectItem* parentBlock;
				BlockEditor* editor;
				int IO;
				Line* line;
				bool isP1 = false;
		};

		// getters
		inline bool isPlaced() const { return placed; };
		inline QVector<BlockIO*> getInputs() const { return input; };
		inline QVector<BlockIO*> getOutputs() const { return output; };
		// setters
		inline void setIsPlaced(bool const placed) { this->placed = placed; };


	private:
		// attributes
		bool placed;
		QVector<BlockIO*> input;
		QVector<BlockIO*> output;
};

