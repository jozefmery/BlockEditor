#include "BlockEditor.h"
#include "Scaler.h"

#include <QBrush>
#include <QComboBox>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QDialog>

BlockEditor::BlockEditor(QWidget* parent) {
	// disable scroll bar
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// set size of view
	resize(Scaler::scaleX(1024), Scaler::scaleY(695));

	// set up scene
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, Scaler::scaleX(1024), Scaler::scaleY(695));
	setScene(scene);

	drawGUI();
}

void BlockEditor::drawGUI() {
	// background
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::darkGray);
	scene->setBackgroundBrush(brush);
}

void BlockEditor::pickUpBlock(Block* block, QPointF pos) {
	if (blockToPlace == nullptr) {
		block->setCursor(Qt::ClosedHandCursor);
		blockToPlace = block;
		mouseClickPos = pos;
		blockToPlace->setIsPlaced(false);
		originalPos = block->pos();
		block->setZValue(1);
	}
}

void BlockEditor::placeBlock(Block* block) {
	// get cursor position
	QPointF cursorPos = mapFromGlobal(QCursor::pos());

	block->setCursor(Qt::OpenHandCursor);

	// shift the position of placed block 
	int shiftX = cursorPos.x() - mouseClickPos.x();
	int shiftY = cursorPos.y() - mouseClickPos.y();
	QPointF newPos(shiftX, shiftY);
	blockToPlace->setPos(newPos);
	blockToPlace->setIsPlaced(true);

	// null the values
	blockToPlace = nullptr;
	mouseClickPos = QPointF(-1, -1);
	block->setZValue(0);
}

void BlockEditor::showContextMenu(QPoint pos) {
	if (blockToPlace == nullptr && !isDrawing()) { // when plock is picked up, context menu isn't able to open
		// Handle global position
		QPoint globalPos = mapToGlobal(pos);

		item = itemAt(pos.x(), pos.y());
		if (item) {
			QMenu myMenu;
			myMenu.addAction("Delete Block", this, SLOT(deleteBlock()));
			myMenu.addAction("Change Operation");
			myMenu.exec(globalPos);
		} else {
			QMenu myMenu;
			myMenu.addAction("New Scheme");
			myMenu.addAction("New Block", this, SLOT(spawnBlock()));
			myMenu.exec(globalPos);
		}
	}
}

void BlockEditor::deleteBlock() {
	scene->removeItem(item);
	blocks.remove(blocks.indexOf(dynamic_cast<Block*>(item), 0));
	item = nullptr;
}

void BlockEditor::spawnBlock() {

	dialog = new Dialog();
	dialog->exec();

	// get cursor position
	QPointF cursorPos = mapFromGlobal(QCursor::pos());
	// draw a block
	Block* block = new Block(cursorPos.x() - 25, cursorPos.y() - 25, this, 
		dialog->getOperation(), dialog->getIPorts(), dialog->getOPorts());

	block->parent = this;

	blocks.push_back(block);
	scene->addItem(block);
	//pickUpBlock(block, cursorPos);
}

void BlockEditor::mouseMoveEvent(QMouseEvent* event) {

	// if there is a cardToPlace, then make it follow the mouse
	if (blockToPlace) {
		int shiftX = event->pos().x() - mouseClickPos.x();
		int shiftY = event->pos().y() - mouseClickPos.y();
		QPointF newPoint(shiftX, shiftY);
		blockToPlace->setPos(newPoint);
	} else if (isDrawing()) {
		line->setLine(lineStart.x(), lineStart.y(), event->pos().x(), event->pos().y());
	}

	QGraphicsView::mouseMoveEvent(event);
}
