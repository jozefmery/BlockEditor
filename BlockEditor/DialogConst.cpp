/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: DialogConst						*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#include "DialogConst.h"

/**
* Constructor of dialog.
* @param parent widget parent
*/
DialogConst::DialogConst(QWidget *parent)
	: QDialog(parent) {

	ui.setupUi(this);

	connect(ui.ok, SIGNAL(clicked()), SLOT(ok()));
	connect(ui.cancel, SIGNAL(clicked()), SLOT(cancel()));

	clickedOk = false;
}

/**
* Slot for signal cliclked on OK button. Get values from widgets.
*/
void DialogConst::ok() {
	value = ui.value->text().toDouble();
	outputType = ui.output->currentText();

	clickedOk = true;

	close();
}

/**
* Slot for signal clicked on Cancel button. Close dialog.
*/
void DialogConst::cancel() {

	clickedOk = false;
	close();
}