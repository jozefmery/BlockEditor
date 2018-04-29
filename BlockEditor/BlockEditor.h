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
	BlockEditor(QWidget* parent = nullptr);

	// methods
	void pickUpBlock(Block* card, QPointF pos);
	void placeBlock(Block* block);

	// getters
	inline BlockSpawner* getSpawner() const { return blockSpawner; };

private:
	// attributes
	QGraphicsItem * item = nullptr;
	QPointF originalPos;
	QPointF mouseClickPos = QPointF(-1, -1);
	Block* blockToPlace = nullptr;
	BlockSpawner* blockSpawner;

	// methods
	void drawGUI();

public slots:
	void showContextMenu(QPoint pos);
	void deleteBlock();
	void spawnBlock();

};

