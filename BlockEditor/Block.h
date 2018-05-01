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
		Block(const int x, const int y, BlockEditor* parent, QString operation, QString input, QString output);
		Block(const int x, const int y, BlockEditor* parent, double value, QString outputType);

		// events
		void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

		BlockEditor *parent;

		class BlockIO : public QGraphicsRectItem {

			public:
				// constructors
				BlockIO(int x, int y, int IO, QString name, double value, BlockEditor* editor, QGraphicsRectItem* parentBlock);

				// events
				void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

				// methods
				void addLine(Line *line, bool isPoint1);
				QVariant itemChange(GraphicsItemChange change, const QVariant &value);
				void moveLineToCenter(QPointF newPos);

				// getters
				QGraphicsLineItem* getLine() const { return line; };
				QString getName() const { return name; };
				double getValue() const { return value; };

				// setters
				void setLine(Line* line);
				void setName(const QString name) { this->name = name; };
				void setValue(const double value) { this->value = value; };

			private:
				// attributes
				QGraphicsRectItem* parentBlock;
				BlockEditor* editor;
				int IO;
				Line* line;
				bool isP1 = false;
				QString name;
				double value;
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

