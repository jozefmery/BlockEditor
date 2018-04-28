#pragma once

#include "Block.h"
#include "BlockSpawner.h"

#include <QGraphicsView>
#include <QGraphicsScene>

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

	private:
		// attributes
		QPointF originalPos;
		QPointF mouseClickPos = QPointF(-1, -1);
		Block* blockToPlace = NULL;
		BlockSpawner* blockSpawner;

		// methods
		void drawGUI();

		public slots:
		void spawnBlock();

};

