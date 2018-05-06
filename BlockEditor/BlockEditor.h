/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: BlockEditor							*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#pragma once

#include "Line.h"
#include "Block.h"
#include "Dialog.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "DialogConst.h"

class BlockEditor : public QGraphicsView {

	Q_OBJECT

	public:
		// attributes
		QGraphicsScene * scene;

		// events
		void mouseMoveEvent(QMouseEvent* event) override;

		// constructors
		explicit BlockEditor(QWidget* parent = nullptr);

		// methods
		void pickUpBlock(Block* block, QPointF pos);
		void placeBlock(Block* block);
		void checkCycle(Block* block);

		// getters
		bool isDrawing() const;
		Line* getLine() const;
		QPointF getLineStart() const;
		Block* getActualBlock() const;
		Block* getResultBlock() const;
		QVector<Block*>& getBlocks();
		QVector<Line*>& getLines();
		QPoint getMousePos() const;

		//setters
		void setIsDrawing(const bool drawing);
		void setLine(Line* line);
		void setLineStart(const QPoint lineStart);
		void setActualBlock(Block* block);
		void setResultBlock(Block* result);

	private:
		// attributes
		QGraphicsItem* item = nullptr;
		QPointF originalPos;
		QPointF mouseClickPos = QPointF(-1, -1);
		Block* blockToPlace = nullptr;
		bool drawing = false;;
		Line* line = nullptr;
		QPointF lineStart = QPointF(-1, -1);
		QVector<Block*> blocks;
		QVector<Line*> lines;
		Dialog* dialog{};
		DialogConst* dialogConst{};
		Block* resultBlock;
		Block* actualBlock;

		// methods
		void drawGUI();
		void removeConnections(Block* actual, bool input, bool output);

	public slots:
		void showContextMenu(QPoint pos);
		void deleteBlock();
		void editBlock();
		void setAsStartBlock();
		void unsetAsStartBlock();
		void spawnBlock();
		void spawnConstBlock();
		void spawnResultBlock();

};

