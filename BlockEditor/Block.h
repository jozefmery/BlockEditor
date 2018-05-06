/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: Block									*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#pragma once

#include <QGraphicsRectItem>

#define INPUT  1
#define OUTPUT 2

#define CONSTBLOCK  1
#define BLOCK		2
#define RESULT		3

class Line;
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
				Line* getLine() const;
				QString getName() const;
				double getValue() const;
				bool isCycle() const;
				bool hasVal() const;

				// setters
				void setLine(Line* line);
				void setName(const QString name);
				void setValue(const double value);
				void setCycle(const bool cycle);
				void setConnectable(const bool connectable);
				void setHasVal(const bool hasValue);

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
				bool hasValue;
		};

		// getters
		bool isPlaced() const;
		QVector<BlockIO*> getInputs() const;
		QVector<BlockIO*> getOutputs() const;
		QString getOperation() const;
		QGraphicsTextItem* getOperationText() const;
		int getBlockType() const;
		bool isActualBlock() const;

		// setters
		void setIsPlaced(bool const placed);
		void setOperation(const QString operation);
		void setOperationText(QGraphicsTextItem* operationText);
		void setBlockType(const int blockType);
		void setActualBlock(const bool startBlock);

	private:
		// attributes
		int blockType;
		bool startBlock;
		bool placed{};
		QString operation;
		QVector<BlockIO*> input;
		QVector<BlockIO*> output;
		QGraphicsTextItem * operationText;

};

