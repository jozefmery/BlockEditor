#pragma once

#include "Line.h"

#include <QGraphicsRectItem>

#define INPUT  1
#define OUTPUT 2

#define CONSTBLOCK  1
#define BLOCK		2

class BlockEditor;

class Block : public QGraphicsRectItem {

	public:
		// constructors
		Block(int x, int y, BlockEditor* parent, QString operation, QString inputType, QString outputType);
		Block(int x, int y, BlockEditor* parent, double value, QString outputType);

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
				void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
				void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

				// methods
				void addLine(Line *line, bool isPoint1);
				QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
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
		QString getOperation() const { return operation; };
		QGraphicsTextItem* getOperationText() const { return operationText; };
		void setOperationText(QString opText);
		int getBlockType() const { return blockType; };
		int getX() const { return x; };
		int getY() const { return y; };

		// setters
		void setIsPlaced(bool const placed) { this->placed = placed; };
		void setOperation(const QString operation) { this->operation = operation; };
		void setOperationText(QGraphicsTextItem* operationText) { this->operationText = operationText; };
		void setBlockType(const int blockType) { this->blockType = blockType; };

	private:
		// attributes
		int blockType;
		bool placed{};
		QString operation;
		QVector<BlockIO*> input;
		QVector<BlockIO*> output;
		QGraphicsTextItem * operationText;
		int x, y;
};

