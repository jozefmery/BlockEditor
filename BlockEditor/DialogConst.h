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

		// setters
		void setOutputType(const QString outputType) { this->outputType = outputType; };
		void setValue(const double value) { this->value = value; };

	private:
		Ui::DialogConst ui;
		QString outputType;
		double value;

	signals:
		void clicked();

	public slots:
		void ok();
		void cancel();
};
