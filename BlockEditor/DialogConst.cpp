/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: DialogConst							*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#include "DialogConst.h"

DialogConst::DialogConst(QWidget *parent)
	: QDialog(parent) {

	ui.setupUi(this);

	connect(ui.ok, SIGNAL(clicked()), SLOT(ok()));
	connect(ui.cancel, SIGNAL(clicked()), SLOT(cancel()));

	clickedOk = false;
}

void DialogConst::ok() {
	value = ui.value->text().toDouble();
	outputType = ui.output->currentText();

	clickedOk = true;

	close();
}

void DialogConst::cancel() {

	clickedOk = false;
	close();
}