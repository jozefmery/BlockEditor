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
		//void mousePressEvent(QMouseEvent* event);

		// constructors
		explicit BlockEditor(QWidget* parent = nullptr);

		// methods
		void pickUpBlock(Block* block, QPointF pos);
		void placeBlock(Block* block);

		// getters
		bool isDrawing() const;
		Line* getLine() const { return line; };
		QPointF getLineStart() const { return lineStart; };

		//setters
		void setIsDrawing(const bool drawing);
		void setLine(Line* line){
			this->line = line;
			lines.push_back(line);
		};
		void setLineStart(const QPoint lineStart) { this->lineStart = mapFromGlobal(lineStart); };

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

		// methods
		void drawGUI();
		void removeConnections(Block* actual);

	public slots:
		void showContextMenu(QPoint pos);
		void deleteBlock();
		void spawnBlock();
		void spawnConstBlock();

};

