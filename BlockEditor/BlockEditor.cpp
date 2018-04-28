#include "BlockEditor.h"

#include <QBrush>
#include <QComboBox>
#include <QMouseEvent>
#include <QDebug>
#include "Scaler.h"

BlockEditor::BlockEditor(QWidget* parent) {
	// disable scroll bar
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// set size of view
	setFixedSize(Scaler::scaleX(1024), Scaler::scaleY(768));

	// set up scene
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, Scaler::scaleX(1024), Scaler::scaleY(768));
	setScene(scene);

	drawGUI();
}

void BlockEditor::drawGUI() {
	// background
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::darkGray);
	scene->setBackgroundBrush(brush);

	// draw a block spawner 
	blockSpawner = new BlockSpawner();
	connect(blockSpawner, SIGNAL(clicked()), this, SLOT(spawnBlock()));
	scene->addItem(blockSpawner);
}

void BlockEditor::pickUpBlock(Block* block, QPointF pos) {
	if (blockToPlace == nullptr) {
		blockToPlace = block;
		mouseClickPos = pos;
		blockToPlace->setIsPlaced(false);
		originalPos = block->pos();
	}
}

void BlockEditor::placeBlock(Block* block) {
	// get cursor position
	QPointF cursorPos = this->mapFromGlobal(QCursor::pos());

	// shift the position of placed block 
	int shiftX = cursorPos.x() - mouseClickPos.x();
	int shiftY = cursorPos.y() - mouseClickPos.y();
	QPointF newPos(shiftX, shiftY);
	blockToPlace->setPos(newPos);
	blockToPlace->setIsPlaced(true);

	// null the values
	blockToPlace = nullptr;
	mouseClickPos = QPointF(-1, -1);
}

void BlockEditor::spawnBlock() {
	// get cursor position
	QPointF cursorPos = this->mapFromGlobal(QCursor::pos());
	// draw a block
	Block* block = new Block(cursorPos.x() - 25, cursorPos.y() - 25, blockSpawner->getBlockOrder());
	scene->addItem(block);
	pickUpBlock(block, cursorPos);
}

void BlockEditor::mouseMoveEvent(QMouseEvent* event) {

	// if there is a cardToPlace, then make it follow the mouse
	if (blockToPlace) {
		int shiftX = event->pos().x() - mouseClickPos.x();
		int shiftY = event->pos().y() - mouseClickPos.y();
		QPointF newPoint(shiftX, shiftY);
		blockToPlace->setPos(newPoint);
	}

	QGraphicsView::mouseMoveEvent(event);
}