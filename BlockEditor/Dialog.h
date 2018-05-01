#pragma once

#include "ui_Dialog.h"

#include <QWidget>
#include <QDialog>

class Dialog : public QDialog {
	Q_OBJECT

	public:
		// constructor
		Dialog(QWidget *parent = Q_NULLPTR);

		// getters
		QString getInputType() const { return inputType; };
		QString getOutputType() const { return outputType; };
		QString getOperation() const { return operation; };

		// setters
		void setInputType(const QString inputType)  { this->inputType = inputType; };
		void setOutputType(const QString outputType) { this->outputType = outputType; };
		void setOperation(const QString operation) { this->operation = operation; };

	private:
		// attributes
		Ui::Dialog ui;
		QString inputType;
		QString outputType;
		QString operation;

	signals:
		void clicked();

	public slots:
		void ok();
		void cancel();
		
};
