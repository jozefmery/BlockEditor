#include "Computation.h"



Computation::Computation(BlockEditor* currentView) {

	this->currentView = currentView;
}

void Computation::process() {
	
	QThread::sleep(3); 
	qDebug() << "yaaaaaaaz";
}