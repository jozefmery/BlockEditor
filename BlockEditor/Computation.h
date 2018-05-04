#pragma once
#include "BlockEditor.h"

#include <QThread>

class Computation : public QObject {

	Q_OBJECT

	public:
		// constructors
		Computation(BlockEditor* currentView);

		// methods

		// getters
		BlockEditor* getCurrentView() const { return currentView; };

		// setters
		void setCurrentView(BlockEditor* currentView) { this->currentView = currentView; };

	private:
		// attributes
		BlockEditor* currentView;

	public slots:
		void process();

	signals:
		void finished();

};

