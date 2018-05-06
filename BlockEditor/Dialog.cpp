/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: Dialog								*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#include "Dialog.h"

#include <QDebug>

Dialog::Dialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.ok, SIGNAL(clicked()), SLOT(ok()));
	connect(ui.cancel, SIGNAL(clicked()), SLOT(cancel()));

	clickedOk = false;
}

void Dialog::ok() {
	inputType = ui.input->currentText();
	outputType = ui.output->currentText();
	operation = ui.opration->currentText();

	clickedOk = true;

	close();
}

void Dialog::cancel() {

	clickedOk = false;

	close();
}
