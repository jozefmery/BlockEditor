#include "BlockEditor.h"
#include "Scaler.h"

#include <QBrush>
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
	brush.setStyle(Qt::Dense1Pattern);
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
		const QPoint globalPos = mapToGlobal(pos);

		item = itemAt(pos.x(), pos.y());
		if (item) {
			if (dynamic_cast<Block*>(item) || dynamic_cast<Block*>(item->parentItem())) {
				QMenu myMenu;
				myMenu.addAction("Delete Block", this, SLOT(deleteBlock()));
				myMenu.addAction("Edit Block");
				myMenu.exec(globalPos);
			} else if (dynamic_cast<Line*>(item)) {
				QMenu myMenu;
				myMenu.addAction("Delete Connection", this, SLOT(deleteBlock()));
				myMenu.exec(globalPos);
			}
		} else {
			QMenu myMenu;
			myMenu.addAction("New Scheme");
			myMenu.addAction("New Block", this, SLOT(spawnBlock()));
			myMenu.exec(globalPos);
		}
	} else if (isDrawing()) {
		item = line;
		setIsDrawing(false);
		deleteBlock();
	}
}

void BlockEditor::removeConnections(Block* actual) {
	QVector<Block::BlockIO*> inputs = actual->getInputs();
	for (Block::BlockIO* input : inputs) {
		if (input->getLine()) {
			item = input->getLine();
			deleteBlock();
		}
	}
	QVector<Block::BlockIO*> outputs = actual->getOutputs();
	for (Block::BlockIO* output : outputs) {
		if (output->getLine()) {
			item = output->getLine();
			deleteBlock();
		}
	}
}

void BlockEditor::deleteBlock() {
	
	if (dynamic_cast<Block*>(item)) {
		blocks.remove(blocks.indexOf(dynamic_cast<Block*>(item), 0));
		scene->removeItem(item);
		removeConnections(dynamic_cast<Block*>(item));
	} else if (dynamic_cast<Block*>(item->parentItem())) {
		blocks.remove(blocks.indexOf(dynamic_cast<Block*>(item->parentItem()), 0));
		scene->removeItem(item->parentItem());
		removeConnections(dynamic_cast<Block*>(item->parentItem()));
	} else if (dynamic_cast<Line*>(item)) {
		lines.remove(lines.indexOf(dynamic_cast<Line*>(item), 0));
		scene->removeItem(item);
		Line* actual = dynamic_cast<Line*>(item);
		for (Block* block: blocks) {
			for (Block::BlockIO* input: block->getInputs()) {
				if (actual == input->getLine()) {
					input->setLine(nullptr);
				}
			}
			for (Block::BlockIO* output : block->getOutputs()) {
				if (actual == output->getLine()) {
					output->setLine(nullptr);
				}
			}
		}
	}

	item = nullptr;
}

void BlockEditor::spawnBlock() {

	dialog = new Dialog();
	dialog->move(QCursor::pos().x() - dialog->width() / 2, 
		QCursor::pos().y() - dialog->height() / 2);
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

	// if there is a blockToPlace, then make it follow the mouse
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


bool BlockEditor::isDrawing() const { return drawing; };

void BlockEditor::setIsDrawing(const bool drawing) {

	if (drawing) {
		for (Block* block : blocks) {
			block->setCursor(Qt::ArrowCursor);
			for (Block::BlockIO* input : block->getInputs()) {
				if (input->getLine() == nullptr && line->getOutBlock() != block) {
					input->setCursor(Qt::PointingHandCursor);
				}
			}
			for (Block::BlockIO* output : block->getOutputs()) {
				output->setCursor(Qt::ArrowCursor);
			}
		}
	} else {
		for (Block* block : blocks) {
			block->setCursor(Qt::OpenHandCursor);
			for (Block::BlockIO* input : block->getInputs()) {
				input->setCursor(Qt::ArrowCursor);
			}
			for (Block::BlockIO* output : block->getOutputs()) {
				if (output->getLine() == nullptr) {
					output->setCursor(Qt::PointingHandCursor);
				}
			}
		}
	}

	this->drawing = drawing;
};



