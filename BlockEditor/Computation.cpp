#include "Computation.h"

#include <QMessageBox>

extern Computation* computation;

/**
 * Constructor.
 * @param currentView current opened view
 */
Computation::Computation(BlockEditor* currentView) {

	this->currentView = currentView;
	this->actualBlock = currentView->getActualBlock();

	result = true;
}

/**
 * Thread run function.
 */
void Computation::run() {

	compute();

	computation = nullptr;
}

/**
 * Recursivly transit blocks and compute results from input ports 
 * and set it to output port. 
 */
void Computation::compute() {

	while (result) {
		if (actualBlock->getBlockType() == CONSTBLOCK) {
			sleep(1);
			Block::BlockIO* output = actualBlock->getOutputs()[0];
			Block::BlockIO* input = output->getLine()->getInPort();
			input->setValue(output->getValue());
			input->setHasVal(true);

			if (output->getLine()->getInBlock()->getBlockType() != RESULT &&
				!currentView->getResultBlock()->getInputs()[0]->hasVal()) {
				currentView->setActualBlock(output->getLine()->getInBlock());
				actualBlock = currentView->getActualBlock();
			} else {
				emit done();
				input->setName(output->getName());
				input->getLine()->setToolTip(input->getName() + ": " + QString::number(input->getValue()));
				result = false;
				currentView->setActualBlock(nullptr);
			}
		}
		else if (actualBlock->getBlockType() == BLOCK) {
			for (Block::BlockIO* input : actualBlock->getInputs()) {
				if (!input->hasVal()) {
					sleep(1);
					if (!currentView->getResultBlock()->getInputs()[0]->hasVal()) {
						currentView->setActualBlock(input->getLine()->getOutBlock());
						actualBlock = currentView->getActualBlock();
						getValue();
					}
					return;
				} 
				
				input->getLine()->setToolTip(input->getName() + ": " + QString::number(input->getValue()));
			}
			sleep(1);
			switch (getOperation()) {
				case '+':
					add();
					break;
				case '-':
					sub();
					break;
				case '*':
					mul();
					break;
				case '/':
					div();
					break;
				default:
					QMessageBox messageBox;
					messageBox.setText("WTF");
			}

			Block::BlockIO* output = actualBlock->getOutputs()[0];
			Block::BlockIO* input = output->getLine()->getInPort();
			input->setValue(output->getValue());
			input->setHasVal(true);

			if (output->getLine()->getInBlock()->getBlockType() != RESULT && 
				!currentView->getResultBlock()->getInputs()[0]->hasVal()) {
				currentView->setActualBlock(output->getLine()->getInBlock());
				actualBlock = currentView->getActualBlock();
			} else {
				emit done();
				input->setName(output->getName());
				input->getLine()->setToolTip(input->getName() + ": " + QString::number(input->getValue()));
				result = false;
				currentView->setActualBlock(nullptr);
			}

		}
	}
}

/**
 * If input port of block hasn't value, search for the nearest
 * block with value on output port.
 */
void Computation::getValue() {
	if (actualBlock->getBlockType() == BLOCK) {
		QVector<Block::BlockIO*> inputs = actualBlock->getInputs();
		for (Block::BlockIO* input : inputs) {
			sleep(1);
			if (!currentView->getResultBlock()->getInputs()[0]->hasVal()) {
				currentView->setActualBlock(input->getLine()->getOutBlock());
				actualBlock = currentView->getActualBlock();
				getValue();
			}
		}
	} else {
		Block::BlockIO* output = actualBlock->getOutputs()[0];
		Block::BlockIO* input = output->getLine()->getInPort();
		input->setValue(output->getValue());
		input->setHasVal(true);
		sleep(1);
		if (!currentView->getResultBlock()->getInputs()[0]->hasVal()) {
			currentView->setActualBlock(output->getLine()->getOutBlock());
			actualBlock = currentView->getActualBlock();
			compute();
		}
	}
}

/**
 * Get type of operation.
 * @return type of operation
 */
int Computation::getOperation() {
	QString operation = actualBlock->getOperation();

	if (operation == "+") {
		return ADD;
	}  
	
	if ( operation == "-") {
		return SUB;
	}

	if (operation == "*") {
		return MUL;
	}

	if (operation == "/") {
		return DIV;
	}

	return -1;
}

/**
 * Add values;
 */
void Computation::add() {
	QVector<double> inputs;
	for (Block::BlockIO* input: actualBlock->getInputs()) {
		inputs.push_back(input->getValue());
	}

	actualBlock->getOutputs()[0]->setValue(inputs[0] + inputs[1]);
	actualBlock->getOutputs()[0]->setHasVal(true);
}

/**
 * Subtract values.
 */
void Computation::sub() {
	QVector<double> inputs;
	for (Block::BlockIO* input : actualBlock->getInputs()) {
		inputs.push_back(input->getValue());
	}

	actualBlock->getOutputs()[0]->setValue(inputs[0] - inputs[1]);
	actualBlock->getOutputs()[0]->setHasVal(true);
}

/**
 * Multiplicate values.
 */
void Computation::mul() {
	QVector<double> inputs;
	for (Block::BlockIO* input : actualBlock->getInputs()) {
		inputs.push_back(input->getValue());
	}

	actualBlock->getOutputs()[0]->setValue(inputs[0] * inputs[1]);
	actualBlock->getOutputs()[0]->setHasVal(true);
}

/**
 * Divide values.
 */
void Computation::div() {
	QVector<double> inputs;
	for (Block::BlockIO* input : actualBlock->getInputs()) {
		inputs.push_back(input->getValue());
	}

	if (inputs[1] == 0) {
		actualBlock->getOutputs()[0]->setValue(0);
		actualBlock->getOutputs()[0]->setHasVal(true);
	} else {
		actualBlock->getOutputs()[0]->setValue(inputs[0] / inputs[1]);
		actualBlock->getOutputs()[0]->setHasVal(true);
	}
}


/**
 * Get current opened view.
 * @return current view
 */
BlockEditor* Computation::getCurrentView() const {
	return currentView;
};

/**
 * Set current opened view.
 * @param currentView current view.
 */
void Computation::setCurrentView(BlockEditor* currentView) {
	this->currentView = currentView;
};