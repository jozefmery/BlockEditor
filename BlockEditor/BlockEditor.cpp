

#include "BlockEditor.h"

#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QDialog>
#include <cmath>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>

static QPoint rightClick;

/**
 * Constructor of a view (central widget of main window).
 * @param parent 
 */
BlockEditor::BlockEditor(QWidget* parent) {

	// set up scene
	scene = new QGraphicsScene();
	setScene(scene);

	actualBlock = nullptr;
	resultBlock = nullptr;

	drawGUI();

	//setAlignment(Qt::AlignLeft | Qt::AlignTop);
}
/**
 * Set background.
 */
void BlockEditor::drawGUI() {
	// background
	QBrush brush;
	brush.setStyle(Qt::Dense1Pattern);
	brush.setColor(Qt::darkGray);
	scene->setBackgroundBrush(brush);
}


/**
 * Sets position of placed block and picks the block up.
 * @param block placed plock
 * @param pos position of placed block
 */
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

/**
 * Places block.
 * @param block block to place
 */
void BlockEditor::placeBlock(Block* block) {
	// get cursor position
	QPointF cursorPos = mapToScene(mapFromGlobal(QCursor::pos()));

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

/**
 * Shows context menu, depending on right-clicked item.
 * @param pos 
 */
void BlockEditor::showContextMenu(QPoint pos) {
	if (blockToPlace == nullptr && !isDrawing()) { // when block is picked up, context menu isn't able to open
		// Handle global position
		const QPoint globalPos = mapToGlobal(pos);

		rightClick = globalPos;

		item = itemAt(pos.x(), pos.y());
		if (item) {
			if (dynamic_cast<Block*>(item)) {
				if (dynamic_cast<Block*>(item)->getBlockType() == RESULT) {
					QMenu myMenu(this);
					myMenu.addAction("Delete Block", this, SLOT(deleteBlock()));
					myMenu.exec(globalPos);
				} else {
					QMenu myMenu(this);
					myMenu.addAction("Delete Block", this, SLOT(deleteBlock()));
					myMenu.addAction("Edit Block", this, SLOT(editBlock()));
					if (!dynamic_cast<Block*>(item)->isActualBlock()) {
						myMenu.addAction("Set as Start", this, SLOT(setAsStartBlock()));
					} else {
						myMenu.addAction("Unset as Start", this, SLOT(unsetAsStartBlock()));
					}
					myMenu.exec(globalPos);
				}
			} else if (dynamic_cast<Block*>(item->parentItem())){
				if (dynamic_cast<Block*>(item->parentItem())->getBlockType() == RESULT) {
					QMenu myMenu(this);
					myMenu.addAction("Delete Block", this, SLOT(deleteBlock()));
					myMenu.exec(globalPos);
				}
				else {
					QMenu myMenu(this);
					myMenu.addAction("Delete Block", this, SLOT(deleteBlock()));
					myMenu.addAction("Edit Block", this, SLOT(editBlock()));
					if (!dynamic_cast<Block*>(item->parentItem())->isActualBlock()) {
						myMenu.addAction("Set as Start", this, SLOT(setAsStartBlock()));
					} else {
						myMenu.addAction("Unset as Start", this, SLOT(unsetAsStartBlock()));
					}
					myMenu.exec(globalPos);
				}
			} else if (dynamic_cast<Line*>(item)) {
				QMenu myMenu(this);
				myMenu.addAction("Delete Connection", this, SLOT(deleteBlock()));
				myMenu.exec(globalPos);
			}
		} else {
			QMenu myMenu(this);
			myMenu.addAction("New Block", this, SLOT(spawnBlock()));
			myMenu.addAction("New Const Block", this, SLOT(spawnConstBlock()));
			myMenu.addAction("New Result Block", this, SLOT(spawnResultBlock()));
			myMenu.exec(globalPos);
		}
	} else if (isDrawing()) {
		item = line;
		setIsDrawing(false);
		deleteBlock();
	}
}

/**
 * Removes connections of given block.
 * @param actual block that connections will be deleted
 * @param input input connection to remove indicator
 * @param output output connection to remove indicator 
 */
void BlockEditor::removeConnections(Block* actual, bool input, bool output) {
	if (input) {
		QVector<Block::BlockIO*> inputs = actual->getInputs();
		for (Block::BlockIO* inputPort : inputs) {
			if (inputPort->getLine()) {
				item = inputPort->getLine();
				deleteBlock();
			}
		}
	}

	if (output) {
		QVector<Block::BlockIO*> outputs = actual->getOutputs();
		for (Block::BlockIO* outputPort : outputs) {
			if (outputPort->getLine()) {
				item = outputPort->getLine();
				deleteBlock();
			}
		}
	}
}

/**
 * Removes block (block to remove is set in showContextMenu slot as
 * attribute item).
 */
void BlockEditor::deleteBlock() {
	
	if (dynamic_cast<Block*>(item)) {
		if (dynamic_cast<Block*>(item)->isActualBlock()) {
			actualBlock = nullptr;
		}
		if (dynamic_cast<Block*>(item)->getBlockType() == RESULT) {
			resultBlock = nullptr;
			scene->removeItem(item);
			removeConnections(dynamic_cast<Block*>(item), true, false);
			return;
		}
		blocks.remove(blocks.indexOf(dynamic_cast<Block*>(item), 0));
		scene->removeItem(item);
		removeConnections(dynamic_cast<Block*>(item), true, true);
	} else if (dynamic_cast<Block*>(item->parentItem())) {
		if (dynamic_cast<Block*>(item->parentItem())->isActualBlock()) {
			actualBlock = nullptr;
		}
		if (dynamic_cast<Block*>(item->parentItem())->getBlockType() == RESULT) {
			resultBlock = nullptr;
			scene->removeItem(item->parentItem());
			removeConnections(dynamic_cast<Block*>(item->parentItem()), true, false);
			return;
		}
		blocks.remove(blocks.indexOf(dynamic_cast<Block*>(item->parentItem()), 0));
		scene->removeItem(item->parentItem());
		removeConnections(dynamic_cast<Block*>(item->parentItem()), true, true);
	} else if (dynamic_cast<Line*>(item)) {
		lines.remove(lines.indexOf(dynamic_cast<Line*>(item), 0));
		scene->removeItem(item);
		Line* actual = dynamic_cast<Line*>(item);

		if (actualBlock) {
			if (actualBlock->getBlockType() == BLOCK) {
				actualBlock->setBrush(QBrush(QColor(Qt::red)));
			} else {
				actualBlock->setBrush(QBrush(QColor(Qt::yellow)));
			}
			actualBlock->setActualBlock(false);
			actualBlock = nullptr;
		}
		
		if (actual->getInBlock()) {
			if (actual->getInBlock()->getBlockType() == RESULT) {
				actual->getInBlock()->getInputs()[0]->setValue(NULL);
				actual->getInBlock()->getInputs()[0]->setName(nullptr);
			}

			for (Block::BlockIO* input : actual->getInBlock()->getInputs()) {
				if (input->getLine() == actual) {
					input->setLine(nullptr);
				}
			}
		}

		for (Block::BlockIO* output : actual->getOutBlock()->getOutputs()) {
			if (output->getLine() == actual) {
				output->setLine(nullptr);
			}
		}
	}

	item = nullptr;
}

/**
 * Edit block, based on user input.
 */
void BlockEditor::editBlock() {

	Block* block;
	if (dynamic_cast<Block*>(item)) {
		block = dynamic_cast<Block*>(item);
	} else {
		block = dynamic_cast<Block*>(item->parentItem());
	}

	QTextCursor cursor(block->getOperationText()->document());
	bool different;
	switch(block->getBlockType()) {
		case BLOCK:
			dialog = new Dialog();
			dialog->move(QCursor::pos().x() - dialog->width() / 2,
				QCursor::pos().y() - dialog->height() / 2);
			dialog->exec();

			if (!dialog->isOK()) {
				return;
			}

			cursor.setPosition(0);
			cursor.select(QTextCursor::WordUnderCursor);
			cursor.beginEditBlock();
			cursor.insertText(dialog->getOperation());
			cursor.endEditBlock();
			cursor.removeSelectedText();

			block->setOperation(dialog->getOperation());

			different = false;
			for (Block::BlockIO* input: block->getInputs()) {
				if (dialog->getInputType() != input->getName()) {
					input->setName(dialog->getInputType());
					different = true;
				}
			}
			if (different) {
				removeConnections(block, true, false);
			}

			different = false;
			for (Block::BlockIO* output: block->getOutputs()) {
				if (dialog->getOutputType() != output->getName()) {
					output->setName(dialog->getOutputType());
					different = true;
				}
			}
			if (different) {
				removeConnections(block, false, true);
			}

			dialog->setClickedOk(false);

			break;
		case CONSTBLOCK:
			dialogConst = new DialogConst();
			dialogConst->move(QCursor::pos().x() - dialogConst->width() / 2,
				QCursor::pos().y() - dialogConst->height() / 2);
			dialogConst->exec();

			if (!dialogConst->isOK()) {
				return;
			}

			cursor.setPosition(0);
			cursor.select(QTextCursor::WordUnderCursor);
			cursor.beginEditBlock();
			cursor.insertText(QString::number(dialogConst->getValue()));
			cursor.endEditBlock();
			cursor.removeSelectedText();

			different = false;
			for (Block::BlockIO* output: block->getOutputs()) {
				if (dialogConst->getOutputType() != output->getName()) {
					different = true;
				}

				output->setValue(dialogConst->getValue());
				output->setName(dialogConst->getOutputType());

				if (output->getLine()) {
					output->getLine()->getInPort()->setHasVal(false);
					output->getLine()->getInPort()->setValue(0);
				}
			}

			if (different) {
				removeConnections(block, false, true);
			}

			dialogConst->setClickedOk(false);

			break;
		default: ;
	}

	item = nullptr;
}

/**
 * Set block as start position.
 */
void BlockEditor::setAsStartBlock() {

	if (resultBlock == nullptr || resultBlock->getInputs()[0]->getLine() == nullptr) {
		QMessageBox messageBox;
		messageBox.setText("Missing connection to Result Block!");
		messageBox.setStyleSheet("QLabel{min-width: 15em;}");
		messageBox.exec();
		return;
	}

	bool missingConnection = false;
	for (Block* block: blocks) {
		for (Block::BlockIO* input: block->getInputs()) {
			if (input->getLine() == nullptr) {
				missingConnection = true;
				break;
			}
		}
		for (Block::BlockIO* output : block->getOutputs()) {
			if (output->getLine() == nullptr) {
				missingConnection = true;
				break;
			}
		}
		if (missingConnection) {
			QMessageBox messageBox;
			messageBox.setText("Some ports are not connected!");
			messageBox.setStyleSheet("QLabel{min-width: 15em;}");
			messageBox.exec();
			return;
		}
	}

	Block* block;
	if (dynamic_cast<Block*>(item)) {
		block = dynamic_cast<Block*>(item);
	} else {
		block = dynamic_cast<Block*>(item->parentItem());
	}

	if (actualBlock) {
		if (actualBlock->getBlockType() == BLOCK) {
			actualBlock->setBrush(QBrush(QColor(Qt::red)));
		} else {
			actualBlock->setBrush(QBrush(QColor(Qt::yellow)));
		}
		actualBlock->setActualBlock(false);
		actualBlock = nullptr;
	}

	actualBlock = block;
	actualBlock->setBrush(QBrush(QColor(Qt::green)));
	actualBlock->setActualBlock(true);
}

/**
 * Unset block as start position.
 */
void BlockEditor::unsetAsStartBlock() {
	if (actualBlock->getBlockType() == BLOCK) {
		actualBlock->setBrush(QBrush(QColor(Qt::red)));
	} else {
		actualBlock->setBrush(QBrush(QColor(Qt::yellow)));
	}
	actualBlock->setActualBlock(false);
	actualBlock = nullptr;
}


/**
 * Spawn block, based on user input.
 */
void BlockEditor::spawnBlock() {

	auto desktop = QApplication::desktop()->availableGeometry();

	dialog = new Dialog(this);
	
	dialog->move(rightClick.x() - dialog->width() / 2, 
		rightClick.y() - dialog->height() / 2);
	dialog->exec();

	if (dialog->isOK()) {
		// get cursor position
		QPointF cursorPos = mapToScene(mapFromGlobal(rightClick));
		// draw a block
		Block* block = new Block(0, 0, this,
			dialog->getOperation(), dialog->getInputType(), dialog->getOutputType());

		blocks.push_back(block);
		scene->addItem(block);
		block->setPos(cursorPos);

		dialog->setClickedOk(false);
	}

	item = nullptr;
}

/**
 * Spawn block, based on user input.
 */
void BlockEditor::spawnConstBlock() {
	
	dialogConst = new DialogConst(this);
	dialogConst->move(rightClick.x() - dialogConst->width() / 2,
		rightClick.y() - dialogConst->height() / 2);
	dialogConst->exec();

	if (dialogConst->isOK()) {
		// get cursor position
		QPointF cursorPos = mapToScene(mapFromGlobal(rightClick));;
		// draw a block
		Block* block = new Block(0, 0, this,
			dialogConst->getValue(), dialogConst->getOutputType());

		blocks.push_back(block);
		scene->addItem(block);
		block->setPos(cursorPos);
		dialogConst->setClickedOk(false);
	}

	item = nullptr;
}

/**
 * Spawn block handling result of cumputation.
 */
void BlockEditor::spawnResultBlock() {

	if (resultBlock == nullptr) {
		// get cursor position
		QPointF cursorPos = mapToScene(mapFromGlobal(rightClick));;
		// draw a block
		Block* block = new Block(0, 0 , this);

		resultBlock = block;

		scene->addItem(block);
		block->setPos(cursorPos);

	} else {
		QMessageBox messageBox;
		messageBox.setText("You cannot have two result blocks in one project!");
		messageBox.setStyleSheet("QLabel{min-width: 20em;}");
		messageBox.exec();
	}

	item = nullptr;
}

/**
 * If block is not placed or if connect is being drawn follow the 
 * mouse. 
 * @param event mouse event
 */
void BlockEditor::mouseMoveEvent(QMouseEvent* event) {

	// if there is a blockToPlace, then make it follow the mouse
	if (blockToPlace) {
		int shiftX = event->pos().x() - mouseClickPos.x();
		int shiftY = event->pos().y() - mouseClickPos.y();
		QPoint newPoint(shiftX, shiftY);
		blockToPlace->setPos(mapToScene(newPoint));
	} else if (isDrawing()) {
		QPoint newPoint(event->pos().x(), event->pos().y());
		newPoint = mapToScene(newPoint).toPoint();
		line->setLine(lineStart.x(), lineStart.y(), newPoint.x(), newPoint.y());
	}

	QGraphicsView::mouseMoveEvent(event);
}

/**
 * Recursively checks weather the connection to input port, doesn't
 * create cycle.
 * @param block 
 */
void BlockEditor::checkCycle(Block* block) {
	
	if (block->getBlockType() == BLOCK) {
		QVector<Block::BlockIO*> inputs = block->getInputs();
		for (Block::BlockIO* input: inputs) {
			if (input->getLine() == nullptr) {
				input->setCycle(true);
			} else {
				checkCycle(input->getLine()->getOutBlock());
			}
		}
	}
}


/**
 * Getter.
 * @return return wether connection is being drawn.
 */
bool BlockEditor::isDrawing() const {
	return drawing;
}

/**
 * Setter.
 * @param drawing conenction is being drawn indicator.
 */
void BlockEditor::setIsDrawing(const bool drawing) {

	if (drawing) {
		checkCycle(line->getOutBlock());
		if (resultBlock) {
			resultBlock->getInputs()[0]->setCursor(Qt::PointingHandCursor);
		}

		for (Block* block : blocks) {
			block->setCursor(Qt::ArrowCursor);
			for (Block::BlockIO* input : block->getInputs()) {
				input->setConnectable(false);
				if (input->getLine() == nullptr && line->getOutBlock() != block &&
					input->getName() == line->getOutBlock()->getOutputs()[0]->getName()
					&& !input->isCycle()) {
			
					input->setConnectable(true);
					input->setCursor(Qt::PointingHandCursor);
					input->setBrush(QBrush(QColor(Qt::green)));
				}
			}
			for (Block::BlockIO* output : block->getOutputs()) {
				output->setCursor(Qt::ArrowCursor);
			}
		}
	} else {
		if (resultBlock) {
			resultBlock->getInputs()[0]->setCursor(Qt::ArrowCursor);
		}
		for (Block* block : blocks) {
			block->setCursor(Qt::OpenHandCursor);
			for (Block::BlockIO* input : block->getInputs()) {
				input->setCursor(Qt::ArrowCursor);
				input->setBrush(QBrush(QColor(Qt::white)));
				input->setCycle(false);
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

/**
 * Set block as current.
 * @param block 
 */
void BlockEditor::setActualBlock(Block* block) {

	if (actualBlock) {
		if (actualBlock->getBlockType() == BLOCK) {
			actualBlock->setBrush(QBrush(QColor(Qt::red)));
		}
		else {
			actualBlock->setBrush(QBrush(QColor(Qt::yellow)));
		}
		actualBlock->setActualBlock(false);
		actualBlock = nullptr;
	}

	actualBlock = block;
	if (actualBlock) {
		actualBlock->setBrush(QBrush(QColor(Qt::green)));
		actualBlock->setActualBlock(true);
	}
}

/**
 * Get connection.
 * @return connection
 */
Line* BlockEditor::getLine() const {
	return line;
};

/**
 * Get connection start.
 * @return connection begin
 */
QPointF BlockEditor::getLineStart() const {
	return lineStart;
};

/**
 * Get current block.
 * @return current block
 */
Block* BlockEditor::getActualBlock() const {
	return actualBlock;
};

/**
 * Get block handling result of computation.
 * @return block handling result of computation
 */
Block* BlockEditor::getResultBlock() const {
	return resultBlock;
};

/**
 * Get all the blocks of scene.
 * @return blocks of scene
 */
QVector<Block*>& BlockEditor::getBlocks() {
	return blocks;
};

/**
 * Get all the connections of scene.
 * @return connections of scene
 */
QVector<Line*>& BlockEditor::getLines() {
	return lines;
};

/**
 * Set connection.
 * @param line conenction
 */
void BlockEditor::setLine(Line* line) {
	this->line = line;
	lines.push_back(line);
};

/**
 * Set connection start position.
 * @param lineStart connection start position
 */
void BlockEditor::setLineStart(const QPoint lineStart) {
	this->lineStart = mapToScene(mapFromGlobal(lineStart));
};


/**
 * Get mouse position.
 * @return mouse position
 */
QPoint BlockEditor::getMousePos() const {
	return mapFromGlobal(QCursor::pos());
}

void BlockEditor::setResultBlock(Block* result){
	
	resultBlock = result;
}
