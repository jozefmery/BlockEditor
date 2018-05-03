

#include "BlockEditor.h"

#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QDialog>
#include <cmath>
#include <QMessageBox>

/**
 * \brief Constructor of a view (central widget of main window).
 * \param parent 
 */
BlockEditor::BlockEditor(QWidget* parent) {
	// disable scroll bar
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// set size of view
	resize(1024, 1024);

	// set up scene
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, 1024, 1024);
	setScene(scene);

	actualBlock = nullptr;
	resultBlock = nullptr;
	
	drawGUI();
}

/**
 * \brief Set background.
 */
void BlockEditor::drawGUI() {
	// background
	QBrush brush;
	brush.setStyle(Qt::Dense1Pattern);
	brush.setColor(Qt::darkGray);
	scene->setBackgroundBrush(brush);
}


/**
 * \brief Sets position of placed block and picks the block up.
 * \param block placed plock
 * \param pos position of placed block
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
 * \brief Places block.
 * \param block block to place
 */
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

/**
 * \brief Shows context menu, depending on right-clicked item.
 * \param pos 
 */
void BlockEditor::showContextMenu(QPoint pos) {
	if (blockToPlace == nullptr && !isDrawing()) { // when plock is picked up, context menu isn't able to open
		// Handle global position
		const QPoint globalPos = mapToGlobal(pos);

		item = itemAt(pos.x(), pos.y());
		if (item) {
			if (dynamic_cast<Block*>(item)) {
				if (dynamic_cast<Block*>(item)->getBlockType() == RESULT) {
					QMenu myMenu;
					myMenu.addAction("Delete Block", this, SLOT(deleteBlock()));
					myMenu.exec(globalPos);
				} else {
					QMenu myMenu;
					myMenu.addAction("Delete Block", this, SLOT(deleteBlock()));
					myMenu.addAction("Edit Block", this, SLOT(editBlock()));
					if (!dynamic_cast<Block*>(item)->isActualBlock()) {
						myMenu.addAction("Set as Start", this, SLOT(setAsStartBlock()));
					}
					myMenu.exec(globalPos);
				}
			} else if (dynamic_cast<Block*>(item->parentItem())){
				if (dynamic_cast<Block*>(item->parentItem())->getBlockType() == RESULT) {
					QMenu myMenu;
					myMenu.addAction("Delete Block", this, SLOT(deleteBlock()));
					myMenu.exec(globalPos);
				}
				else {
					QMenu myMenu;
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
				QMenu myMenu;
				myMenu.addAction("Delete Connection", this, SLOT(deleteBlock()));
				myMenu.exec(globalPos);
			}
		} else {
			QMenu myMenu;
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
 * \brief Removes connections of given block.
 * \param actual block that connections will be deleted
 * \param input input connection to remove indicator
 * \param output output connection to remove indicator 
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
 * \brief Removes block (block to remove is set in showContextMenu slot as
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
			scene->removeItem(item);
			removeConnections(dynamic_cast<Block*>(item), true, false);
			return;
		}
		blocks.remove(blocks.indexOf(dynamic_cast<Block*>(item->parentItem()), 0));
		scene->removeItem(item->parentItem());
		removeConnections(dynamic_cast<Block*>(item->parentItem()), true, true);
	} else if (dynamic_cast<Line*>(item)) {
		lines.remove(lines.indexOf(dynamic_cast<Line*>(item), 0));
		scene->removeItem(item);
		Line* actual = dynamic_cast<Line*>(item);
		QVector<Block*> inOut;
		inOut.push_back(actual->getOutBlock());
		if (actual->getInBlock()) {
			inOut.push_back(actual->getInBlock());
		}
		for (Block* block: inOut) {
			if (actualBlock) {
				if (actualBlock->getBlockType() == BLOCK) {
					actualBlock->setBrush(QBrush(QColor(Qt::red)));
				} else {
					actualBlock->setBrush(QBrush(QColor(Qt::yellow)));
				}
				actualBlock->setActualBlock(false);
				actualBlock = nullptr;
			}
			if (block->getBlockType() == RESULT) {
				block->getInputs()[0]->setValue(NULL);
				block->getInputs()[0]->setName(nullptr);
			}
			for (Block::BlockIO* input: block->getInputs()) {
				if (actual->getInBlock() == block && input->getLine() == line) {
					input->setLine(nullptr);
				}
			}
			for (Block::BlockIO* output : block->getOutputs()) {
				if (actual->getOutBlock() == block && output->getLine() == line) {
					output->setLine(nullptr);
				}
			}
		}
	}

	item = nullptr;
}

/**
 * \brief Edit block, based on user input.
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

			cursor.select(QTextCursor::WordUnderCursor);
			cursor.beginEditBlock();
			cursor.insertText(QString::number(dialogConst->getValue()));
			cursor.endEditBlock();
			cursor.removeSelectedText();

			different = false;
			for (Block::BlockIO* output: block->getOutputs()) {
				if (dialogConst->getOutputType() != output->getName()) {
					output->setValue(dialogConst->getValue());
					output->setName(dialogConst->getOutputType());
					different = true;
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

void BlockEditor::setAsStartBlock() {

	if (resultBlock == nullptr || resultBlock->getInputs()[0]->getLine() == nullptr) {
		QMessageBox messageBox;
		messageBox.setText("Missing connection to Result Block!");
		messageBox.setStyleSheet("QLabel{min-width: 350px;}");
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
			messageBox.setStyleSheet("QLabel{min-width: 350px;}");
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
 * \brief Spawn block, based on user input.
 */
void BlockEditor::spawnBlock() {

	dialog = new Dialog();
	dialog->move(QCursor::pos().x() - dialog->width() / 2, 
		QCursor::pos().y() - dialog->height() / 2);
	dialog->exec();

	if (dialog->isOK()) {
		// get cursor position
		QPointF cursorPos = mapFromGlobal(QCursor::pos());
		// draw a block
		Block* block = new Block(cursorPos.x() - 25, cursorPos.y() - 25, this,
			dialog->getOperation(), dialog->getInputType(), dialog->getOutputType());

		blocks.push_back(block);
		scene->addItem(block);

		dialog->setClickedOk(false);
	}

	item = nullptr;
}

/**
 * \brief Spawn block, based on user input.
 */
void BlockEditor::spawnConstBlock() {
	
	dialogConst = new DialogConst();
	dialogConst->move(QCursor::pos().x() - dialogConst->width() / 2,
		QCursor::pos().y() - dialogConst->height() / 2);
	dialogConst->exec();

	if (dialogConst->isOK()) {
		// get cursor position
		QPointF cursorPos = mapFromGlobal(QCursor::pos());
		// draw a block
		Block* block = new Block(cursorPos.x() - 25, cursorPos.y() - 25, this,
			std::floor((dialogConst->getValue() * 100) + .5) / 100, dialogConst->getOutputType());

		blocks.push_back(block);
		scene->addItem(block);

		dialogConst->setClickedOk(false);
	}

	item = nullptr;
}

void BlockEditor::spawnResultBlock() {

	if (resultBlock == nullptr) {
		// get cursor position
		QPointF cursorPos = mapFromGlobal(QCursor::pos());
		// draw a block
		Block* block = new Block(cursorPos.x() - 25, cursorPos.y() - 25, this);

		resultBlock = block;

		scene->addItem(block);
	} else {
		QMessageBox messageBox;
		messageBox.setText("You cannot have two result blocks in one project!");
		messageBox.setStyleSheet("QLabel{min-width: 350px;}");
		messageBox.exec();
	}

	item = nullptr;
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

/**
 * \brief Recursively checks weather the connection to input port, doesn't
 * create cycle.
 * \param block 
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
 * \brief Getter.
 * \return return wether connection is being drawn.
 */
bool BlockEditor::isDrawing() const { return drawing; }

/**
 * \brief Setter.
 * \param drawing conenction is being drawn indicator.
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
 * \brief ???
 * \param event 
 */
void BlockEditor::resizeEvent(QResizeEvent *event)
{
	auto size = event->size();

	scene->setSceneRect(0, 0, size.width(), size.height());
}
