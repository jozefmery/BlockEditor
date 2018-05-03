#pragma once

#include "Line.h"

#include <QGraphicsRectItem>

#define INPUT  1
#define OUTPUT 2

#define CONSTBLOCK  1
#define BLOCK		2
#define RESULT		3

class BlockEditor;

class Block : public QGraphicsRectItem {

	public:
		// constructors
		Block(int x, int y, BlockEditor* parent, QString operation, QString inputType, QString outputType);
		Block(int x, int y, BlockEditor* parent, double value, QString outputType);
		Block(int x, int y, BlockEditor* parent);

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
				Line* getLine() const { return line; };
				QString getName() const { return name; };
				double getValue() const { return value; };
				bool isCycle() const { return cycle; };

				// setters
				void setLine(Line* line);
				void setName(const QString name) { this->name = name; };
				void setValue(const double value) { this->value = value; };
				void setCycle(const bool cycle) { this->cycle = cycle; };
				void setConnectable(const bool connectable) { this->connectable = connectable; };

			private:
				// attributes
				QGraphicsRectItem* parentBlock;
				BlockEditor* editor;
				int IO;
				Line* line;
				bool isP1 = false;
				QString name;
				double value;
				bool cycle;
				bool connectable;
		};

		// getters
		bool isPlaced() const { return placed; };
		QVector<BlockIO*> getInputs() const { return input; };
		QVector<BlockIO*> getOutputs() const { return output; };
		QString getOperation() const { return operation; };
		QGraphicsTextItem* getOperationText() const { return operationText; };
		int getBlockType() const { return blockType; };

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

};

