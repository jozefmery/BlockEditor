/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: DialogConbst							*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#pragma once

#include "ui_DialogConst.h"

#include <QWidget>
#include <QDialog>

class DialogConst : public QDialog
{
	Q_OBJECT

	public:
		// constructors
		DialogConst(QWidget *parent = Q_NULLPTR);

		// getters
		QString getOutputType() const { return outputType; };
		double getValue() const { return value; };
		bool isOK() const { return clickedOk; };

		// setters
		void setOutputType(const QString outputType) { this->outputType = outputType; };
		void setValue(const double value) { this->value = value; };
		void setClickedOk(const bool clickedOk) { this->clickedOk = clickedOk; };

	private:
		// attributes
		Ui::DialogConst ui;
		QString outputType;
		double value;
		bool clickedOk;

	signals:
		void clicked();

	public slots:
		void ok();
		void cancel();
};
