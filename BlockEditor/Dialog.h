/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: Dialog								*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

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
		bool isOK() const { return clickedOk; };

		// setters
		void setInputType(const QString inputType)  { this->inputType = inputType; };
		void setOutputType(const QString outputType) { this->outputType = outputType; };
		void setOperation(const QString operation) { this->operation = operation; };
		void setClickedOk(const bool clickedOk) { this->clickedOk = clickedOk; };

	private:
		// attributes
		Ui::Dialog ui;
		QString inputType;
		QString outputType;
		QString operation;
		bool clickedOk;

	signals:
		void clicked();

	public slots:
		void ok();
		void cancel();
		
};
