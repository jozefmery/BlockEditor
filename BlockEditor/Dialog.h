#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_Dialog.h"

class Dialog : public QDialog {
	Q_OBJECT

	public:
		// constructor
		Dialog(QWidget *parent = Q_NULLPTR);

		// getters
		inline int getIPorts() const { return iPorts; };
		inline int getOPorts() const { return oPorts; };
		inline QString getOperation() const { return operation; };

		// setters
		inline void setIPorts(const int iPorts)  { this->iPorts = iPorts; };
		inline void setOPorts(const int oPorts) { this->oPorts = oPorts; };
		inline void setOperation(const QString operation) { this->operation = operation; };

	private:
		// attributes
		Ui::Dialog ui;
		int iPorts;
		int oPorts;
		QString operation;

	signals:
		void clicked();

	public slots:
		void ok();
		void cancel();
		
};
