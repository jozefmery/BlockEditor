#pragma once

#include "Block.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>

class BlockEditor : public QGraphicsView {

	Q_OBJECT

	public:
		// attributes
		QGraphicsScene * scene;

		// events
		void mouseMoveEvent(QMouseEvent* event);

		// constructors
		BlockEditor(QWidget* parent = NULL);

		// methods
		void pickUpBlock(Block* card, QPointF pos);
		void placeBlock(Block* block);

		// getters
		inline bool isDrawing() const { return drawing; };
		inline QGraphicsLineItem* getLine() const { return line; };
		inline QPointF getLineStart() const { return lineStart; };

		//setters
		inline void setIsDrawing(const bool drawing) { this->drawing = drawing; };
		inline void setLine(QGraphicsLineItem* line) { this->line = line; };
		inline void setLineStart(const QPoint lineStart) { this->lineStart = mapFromGlobal(lineStart); };

	private:
		// attributes
		QGraphicsItem * item = nullptr;
		QPointF originalPos;
		QPointF mouseClickPos = QPointF(-1, -1);
		Block* blockToPlace = NULL;
		bool drawing = false;;
		QGraphicsLineItem* line = NULL;
		QPointF lineStart = QPointF(-1, -1);

		// methods
		void drawGUI();

	public slots:
		void showContextMenu(QPoint pos);
		void deleteBlock();
		void spawnBlock();

};

